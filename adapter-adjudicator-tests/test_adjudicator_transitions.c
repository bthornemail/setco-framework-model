/**
 * @file test_adjudicator_transitions.c
 * @brief Test adjudication state transitions
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
    printf("Test: adjudicator_transitions_test\n");
    
    /* Initialize */
    int result = adjudicator_init();
    assert(result == 0);
    
    /* Test 1: DECLARED → UNDER_REVIEW → GRANTED */
    parsed_declaration_t decl1 = make_valid_decl("adapter-1");
    assert(adjudicator_submit(&decl1) == 0);
    assert(adjudicator_review("adapter-1") == 0);
    
    const adjudicator_record_t* rec1 = adjudicator_lookup("adapter-1");
    assert(rec1->state == ADJUDICATION_STATE_UNDER_REVIEW);
    
    assert(adjudicator_grant("adapter-1", ADEC_FLAG_SOURCE_READ) == 0);
    rec1 = adjudicator_lookup("adapter-1");
    assert(rec1->state == ADJUDICATION_STATE_GRANTED);
    assert(rec1->grant_flags == ADEC_FLAG_SOURCE_READ);
    
    /* Test 2: DECLARED → UNDER_REVIEW → DENIED */
    parsed_declaration_t decl2 = make_valid_decl("adapter-2");
    assert(adjudicator_submit(&decl2) == 0);
    assert(adjudicator_review("adapter-2") == 0);
    assert(adjudicator_deny("adapter-2", "Not needed") == 0);
    
    const adjudicator_record_t* rec2 = adjudicator_lookup("adapter-2");
    assert(rec2->state == ADJUDICATION_STATE_DENIED);
    assert(strcmp(rec2->denial_reason, "Not needed") == 0);
    
    /* Test 3: GRANTED → SUSPENDED → GRANTED (lift) */
    assert(adjudicator_suspend("adapter-1") == 0);
    rec1 = adjudicator_lookup("adapter-1");
    assert(rec1->state == ADJUDICATION_STATE_SUSPENDED);
    
    assert(adjudicator_lift_suspension("adapter-1") == 0);
    rec1 = adjudicator_lookup("adapter-1");
    assert(rec1->state == ADJUDICATION_STATE_GRANTED);
    
    /* Test 4: GRANTED → REVOKED */
    assert(adjudicator_revoke("adapter-1") == 0);
    rec1 = adjudicator_lookup("adapter-1");
    assert(rec1->state == ADJUDICATION_STATE_REVOKED);
    assert(rec1->grant_flags == 0);
    
    /* Test 5: Invalid transitions */
    assert(adjudicator_review("adapter-2") == -3); /* DENIED can't be reviewed */
    assert(adjudicator_grant("adapter-2", 0) == -3); /* DENIED can't be granted */
    
    /* Test 6: Unknown adapter */
    assert(adjudicator_review("nonexistent") == -2);
    
    printf("  PASS\n");
    return 0;
}
