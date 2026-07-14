/**
 * @file test_dispatcher_dispatch.c
 * @brief Test dispatching calls
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../runtime-dispatcher.h"
#include "../adapter-connection-gate.h"
#include "../adapter-adjudicator.h"
#include "../adapter-parser.h"
#include "../runtime-kernel.h"

/* Helper: build a valid parsed declaration */
static parsed_declaration_t make_valid_decl(const char* id, uint32_t flags) {
    parsed_declaration_t decl = {0};
    decl.magic = ADEC_MAGIC;
    decl.version = ADEC_VERSION;
    strncpy(decl.adapter_id, id, 255);
    strncpy(decl.adapter_name, "Test Adapter", 255);
    strncpy(decl.adapter_version, "1.0.0", 63);
    strncpy(decl.adapter_purpose, "Test", 511);
    decl.flags = flags;
    decl.request_source_read = (flags & ADEC_FLAG_SOURCE_READ) != 0;
    decl.request_receipt_consumption = (flags & ADEC_FLAG_RECEIPT_CONSUMPTION) != 0;
    decl.request_runtime_connection = (flags & ADEC_FLAG_RUNTIME_CONNECTION) != 0;
    decl.valid = true;
    decl.error = ADEC_OK;
    return decl;
}

int main(void) {
    printf("Test: dispatcher_dispatch_test\n");
    
    /* Initialize all systems */
    assert(adapter_parser_init() == 0);
    assert(adjudicator_init() == 0);
    assert(gate_init() == 0);
    assert(dispatcher_init() == 0);
    assert(kernel_init() == 0);
    
    /* Setup connected adapter with authority */
    parsed_declaration_t decl = make_valid_decl("adapter-1", 
        ADEC_FLAG_SOURCE_READ | ADEC_FLAG_RUNTIME_CONNECTION);
    assert(adjudicator_submit(&decl) == 0);
    assert(adjudicator_review("adapter-1") == 0);
    /* Grant source_read + runtime_connection */
    assert(adjudicator_grant("adapter-1", ADEC_FLAG_SOURCE_READ | ADEC_FLAG_RUNTIME_CONNECTION) == 0);
    assert(gate_connect("adapter-1") == 0);
    
    /* Test 1: Dispatch pair_cons8 */
    dispatch_result_t r1 = dispatcher_dispatch("adapter-1", FUNC_PAIR_CONS8, 0x01, 0x02);
    assert(r1.success == true);
    assert(r1.result == 0x0102);
    
    /* Test 2: Dispatch pair_car8 */
    dispatch_result_t r2 = dispatcher_dispatch("adapter-1", FUNC_PAIR_CAR8, 0x0102, 0);
    assert(r2.success == true);
    assert(r2.result == 0x01);
    
    /* Test 3: Dispatch pair_cdr8 */
    dispatch_result_t r3 = dispatcher_dispatch("adapter-1", FUNC_PAIR_CDR8, 0x0102, 0);
    assert(r3.success == true);
    assert(r3.result == 0x02);
    
    /* Test 4: Dispatch with disconnected adapter */
    dispatch_result_t r4 = dispatcher_dispatch("adapter-2", FUNC_PAIR_CONS8, 0x01, 0x02);
    assert(r4.success == false);
    
    /* Test 5: Dispatch with nonexistent function */
    dispatch_result_t r5 = dispatcher_dispatch("adapter-1", FUNC_COUNT, 0, 0);
    assert(r5.success == false);
    
    printf("  PASS\n");
    return 0;
}
