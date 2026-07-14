/**
 * @file test_gate_connect.c
 * @brief Test connection gate connect/disconnect
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
    printf("Test: gate_connect_test\n");
    
    /* Initialize */
    assert(adapter_parser_init() == 0);
    assert(adjudicator_init() == 0);
    assert(gate_init() == 0);
    
    /* Test 1: Connect allowed adapter */
    parsed_declaration_t decl1 = make_valid_decl("adapter-1", ADEC_FLAG_RUNTIME_CONNECTION);
    assert(adjudicator_submit(&decl1) == 0);
    assert(adjudicator_review("adapter-1") == 0);
    assert(adjudicator_grant("adapter-1", ADEC_FLAG_RUNTIME_CONNECTION) == 0);
    
    int r1 = gate_connect("adapter-1");
    assert(r1 == 0);
    assert(gate_is_connected("adapter-1") == true);
    
    /* Test 2: Status shows connected */
    gate_status_t status = gate_status("adapter-1");
    assert(status.connected == true);
    assert(status.has_connection_flag == true);
    
    /* Test 3: Connect denied adapter */
    parsed_declaration_t decl2 = make_valid_decl("adapter-2", ADEC_FLAG_SOURCE_READ);
    assert(adjudicator_submit(&decl2) == 0);
    assert(adjudicator_review("adapter-2") == 0);
    assert(adjudicator_grant("adapter-2", ADEC_FLAG_SOURCE_READ) == 0);
    
    int r2 = gate_connect("adapter-2");
    assert(r2 == -2); /* No connection flag */
    assert(gate_is_connected("adapter-2") == false);
    
    /* Test 4: Disconnect */
    int r3 = gate_disconnect("adapter-1");
    assert(r3 == 0);
    assert(gate_is_connected("adapter-1") == false);
    
    /* Test 5: Double connect (should be idempotent) */
    assert(gate_connect("adapter-1") == 0);
    assert(gate_connect("adapter-1") == 0);
    assert(gate_is_connected("adapter-1") == true);
    
    printf("  PASS\n");
    return 0;
}
