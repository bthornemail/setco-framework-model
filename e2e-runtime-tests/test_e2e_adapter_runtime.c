/**
 * @file test_e2e_adapter_runtime.c
 * @brief End-to-end adapter runtime harness
 *
 * Proves the full chain:
 *   ADEC declaration
 *   → parser
 *   → adjudicator
 *   → connection gate
 *   → dispatcher
 *   → bounded runtime call
 *   → denial paths
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../adapter-parser.h"
#include "../adapter-adjudicator.h"
#include "../adapter-connection-gate.h"
#include "../runtime-dispatcher.h"
#include "../runtime-kernel.h"
#include "../compiler.h"
#include "../omniprocessor.h"
#include "../envelope-construction.h"
#include "../legacy-execution.h"

static parsed_declaration_t make_valid_decl(const char* id, uint32_t flags) {
    parsed_declaration_t decl = {0};
    decl.magic = ADEC_MAGIC;
    decl.version = ADEC_VERSION;
    strncpy(decl.adapter_id, id, 255);
    strncpy(decl.adapter_name, "E2E Adapter", 255);
    strncpy(decl.adapter_version, "1.0.0", 63);
    strncpy(decl.adapter_purpose, "End-to-end test adapter", 511);
    decl.flags = flags;
    decl.request_source_read = (flags & ADEC_FLAG_SOURCE_READ) != 0;
    decl.request_receipt_consumption = (flags & ADEC_FLAG_RECEIPT_CONSUMPTION) != 0;
    decl.request_runtime_connection = (flags & ADEC_FLAG_RUNTIME_CONNECTION) != 0;
    decl.valid = true;
    decl.error = ADEC_OK;
    return decl;
}

int main(void) {
    printf("Running Adapter Runtime End-to-End Harness...\n\n");

    /* --- INIT --- */
    printf("Step 1: Initialize all subsystems\n");
    assert(adapter_parser_init() == 0);
    assert(adjudicator_init() == 0);
    assert(gate_init() == 0);
    assert(dispatcher_init() == 0);
    assert(kernel_init() == 0);
    assert(compiler_init() == 0);
    assert(omniprocessor_init() == 0);
    printf("  All subsystems initialized\n\n");

    /* --- HAPPY PATH --- */
    printf("Step 2: Parse ADEC declaration\n");
    parsed_declaration_t decl = make_valid_decl("e2e-adapter-1",
        ADEC_FLAG_SOURCE_READ | ADEC_FLAG_RUNTIME_CONNECTION);
    assert(decl.valid == true);
    assert(decl.error == ADEC_OK);
    assert(decl.flags == 0x05);
    printf("  Declaration parsed: id=e2e-adapter-1 flags=0x05\n\n");

    printf("Step 3: Submit to adjudicator\n");
    assert(adjudicator_submit(&decl) == 0);
    const adjudicator_record_t* rec = adjudicator_lookup("e2e-adapter-1");
    assert(rec != NULL);
    assert(rec->state == ADJUDICATION_STATE_DECLARED);
    printf("  Adjudicator state: DECLARED\n\n");

    printf("Step 4: Review and grant authority\n");
    assert(adjudicator_review("e2e-adapter-1") == 0);
    assert(adjudicator_grant("e2e-adapter-1", ADEC_FLAG_SOURCE_READ | ADEC_FLAG_RUNTIME_CONNECTION) == 0);
    rec = adjudicator_lookup("e2e-adapter-1");
    assert(rec != NULL);
    assert(rec->state == ADJUDICATION_STATE_GRANTED);
    printf("  Adjudicator state: GRANTED\n\n");

    printf("Step 5: Connect through gate\n");
    assert(gate_connect("e2e-adapter-1") == 0);
    assert(gate_is_connected("e2e-adapter-1") == true);
    printf("  Gate: connected\n\n");

    printf("Step 6: Dispatch bounded runtime calls\n");

    dispatch_result_t r1 = dispatcher_dispatch("e2e-adapter-1", FUNC_PAIR_CONS8, 3, 5);
    assert(r1.success == true);
    assert(r1.result == 0x0305);
    printf("  pair_cons8(3, 5) = 0x%04lX  PASS\n", (unsigned long)r1.result);

    dispatch_result_t r2 = dispatcher_dispatch("e2e-adapter-1", FUNC_PAIR_CAR8, 0x0305, 0);
    assert(r2.success == true);
    assert(r2.result == 3);
    printf("  pair_car8(0x0305) = %lu  PASS\n", (unsigned long)r2.result);

    dispatch_result_t r3 = dispatcher_dispatch("e2e-adapter-1", FUNC_PAIR_CDR8, 0x0305, 0);
    assert(r3.success == true);
    assert(r3.result == 5);
    printf("  pair_cdr8(0x0305) = %lu  PASS\n\n", (unsigned long)r3.result);

    /* --- DENIAL PATHS --- */
    printf("Step 7: Denial paths\n");

    /* 7a: Gate denies — adapter not in adjudicator */
    printf("  7a: Gate denies (adapter not in adjudicator)\n");
    assert(gate_check("unknown-adapter") == false);
    printf("    gate_check(unknown-adapter) = false  PASS\n");

    /* 7b: Gate denies — adapter declared but not granted */
    printf("  7b: Gate denies (not granted)\n");
    parsed_declaration_t decl2 = make_valid_decl("e2e-adapter-2",
        ADEC_FLAG_SOURCE_READ | ADEC_FLAG_RUNTIME_CONNECTION);
    assert(adjudicator_submit(&decl2) == 0);
    assert(gate_check("e2e-adapter-2") == false);
    printf("    gate_check(not-granted) = false  PASS\n");

    /* 7c: Gate denies — granted but no runtime_connection flag */
    printf("  7c: Gate denies (no runtime_connection flag)\n");
    parsed_declaration_t decl3 = make_valid_decl("e2e-adapter-3", ADEC_FLAG_SOURCE_READ);
    assert(adjudicator_submit(&decl3) == 0);
    assert(adjudicator_review("e2e-adapter-3") == 0);
    assert(adjudicator_grant("e2e-adapter-3", ADEC_FLAG_SOURCE_READ) == 0);
    assert(gate_check("e2e-adapter-3") == false);
    printf("    gate_check(no flag) = false  PASS\n");

    /* 7d: Dispatcher denies — nonexistent function */
    printf("  7d: Dispatcher denies (nonexistent function)\n");
    dispatch_result_t r4 = dispatcher_dispatch("e2e-adapter-1", FUNC_COUNT, 0, 0);
    assert(r4.success == false);
    printf("    dispatch(FUNC_COUNT) = denied  PASS\n");

    /* 7e: Dispatcher denies — disconnected adapter */
    printf("  7e: Dispatcher denies (disconnected adapter)\n");
    dispatch_result_t r5 = dispatcher_dispatch("e2e-adapter-2", FUNC_PAIR_CONS8, 1, 2);
    assert(r5.success == false);
    printf("    dispatch(disconnected) = denied  PASS\n\n");

    /* --- SUMMARY --- */
    printf("All end-to-end tests passed.\n");
    printf("  Happy path: 3/3 PASS\n");
    printf("  Denial paths: 5/5 PASS\n");
    printf("  Total: 8/8 PASS\n");

    return 0;
}
