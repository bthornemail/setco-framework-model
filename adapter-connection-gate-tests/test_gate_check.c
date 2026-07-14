/**
 * @file test_gate_check.c
 * @brief Test connection gate check
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../adapter-connection-gate.h"
#include "../adapter-adjudicator.h"
#include "../adapter-parser.h"

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
    printf("Test: gate_check_test\n");
    
    /* Initialize */
    assert(adapter_parser_init() == 0);
    assert(adjudicator_init() == 0);
    assert(gate_init() == 0);
    
    /* Test 1: Adapter not found */
    assert(gate_check("nonexistent") == false);
    assert(gate_last_error() == GATE_ERR_ADAPTER_NOT_FOUND);
    
    /* Test 2: Adapter DECLARED (not granted) */
    parsed_declaration_t decl1 = make_valid_decl("adapter-1", ADEC_FLAG_RUNTIME_CONNECTION);
    assert(adjudicator_submit(&decl1) == 0);
    assert(gate_check("adapter-1") == false);
    assert(gate_last_error() == GATE_ERR_NOT_GRANTED);
    
    /* Test 3: Adapter GRANTED but no connection flag */
    assert(adjudicator_review("adapter-1") == 0);
    assert(adjudicator_grant("adapter-1", ADEC_FLAG_SOURCE_READ) == 0);
    assert(gate_check("adapter-1") == false);
    assert(gate_last_error() == GATE_ERR_NO_CONNECTION_FLAG);
    
    /* Test 4: Adapter GRANTED with connection flag */
    parsed_declaration_t decl2 = make_valid_decl("adapter-2", ADEC_FLAG_RUNTIME_CONNECTION);
    assert(adjudicator_submit(&decl2) == 0);
    assert(adjudicator_review("adapter-2") == 0);
    assert(adjudicator_grant("adapter-2", ADEC_FLAG_RUNTIME_CONNECTION) == 0);
    assert(gate_check("adapter-2") == true);
    
    /* Test 5: Adapter SUSPENDED */
    assert(adjudicator_suspend("adapter-2") == 0);
    assert(gate_check("adapter-2") == false);
    assert(gate_last_error() == GATE_ERR_SUSPENDED);
    
    /* Test 6: Adapter REVOKED */
    assert(adjudicator_lift_suspension("adapter-2") == 0);
    assert(adjudicator_revoke("adapter-2") == 0);
    assert(gate_check("adapter-2") == false);
    assert(gate_last_error() == GATE_ERR_REVOKED);
    
    printf("  PASS\n");
    return 0;
}
