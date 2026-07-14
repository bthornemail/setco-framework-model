/**
 * @file test_adjudicator_submit.c
 * @brief Test adapter submission
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../adapter-adjudicator.h"

/* Helper: build a valid parsed declaration */
static parsed_declaration_t make_valid_decl(const char* id) {
    parsed_declaration_t decl = {0};
    decl.magic = ADEC_MAGIC;
    decl.version = ADEC_VERSION;
    strncpy(decl.adapter_id, id, 255);
    strncpy(decl.adapter_name, "Test Adapter", 255);
    strncpy(decl.adapter_version, "1.0.0", 63);
    strncpy(decl.adapter_purpose, "Test", 511);
    decl.flags = ADEC_FLAG_SOURCE_READ;
    decl.request_source_read = true;
    decl.valid = true;
    decl.error = ADEC_OK;
    return decl;
}

int main(void) {
    printf("Test: adjudicator_submit_test\n");
    
    /* Initialize */
    int result = adjudicator_init();
    assert(result == 0);
    
    /* Test 1: Submit valid declaration */
    parsed_declaration_t decl1 = make_valid_decl("adapter-1");
    int r1 = adjudicator_submit(&decl1);
    assert(r1 == 0);
    
    /* Test 2: Check state is DECLARED */
    const adjudicator_record_t* rec1 = adjudicator_lookup("adapter-1");
    assert(rec1 != NULL);
    assert(rec1->state == ADJUDICATION_STATE_DECLARED);
    
    /* Test 3: Submit duplicate (should fail) */
    int r2 = adjudicator_submit(&decl1);
    assert(r2 == -3);
    
    /* Test 4: Submit NULL (should fail) */
    int r3 = adjudicator_submit(NULL);
    assert(r3 == -2);
    
    /* Test 5: Submit invalid declaration */
    parsed_declaration_t bad_decl = {0};
    bad_decl.valid = false;
    int r4 = adjudicator_submit(&bad_decl);
    assert(r4 == -2);
    
    printf("  PASS\n");
    return 0;
}
