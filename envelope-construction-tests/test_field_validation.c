/**
 * @file test_field_validation.c
 * @brief Test envelope field validation
 */

#include <stdio.h>
#include <assert.h>
#include "../envelope-construction.h"

int main(void) {
    printf("Test: field_validation_test\n");
    
    /* Initialize envelope construction */
    int result = envelope_init();
    assert(result == 0);
    
    /* Test 1: Valid provenance (16 bits) */
    envelope_result_t r1 = envelope_validate_field(FIELD_PROVENANCE, 0xFFFF);
    assert(r1.valid == true);
    
    /* Test 2: Invalid provenance (too large) */
    envelope_result_t r2 = envelope_validate_field(FIELD_PROVENANCE, 0x1FFFF);
    assert(r2.valid == false);
    
    /* Test 3: Valid steps (8 bits) */
    envelope_result_t r3 = envelope_validate_field(FIELD_STEPS, 0xFF);
    assert(r3.valid == true);
    
    /* Test 4: Invalid steps (too large) */
    envelope_result_t r4 = envelope_validate_field(FIELD_STEPS, 0x1FF);
    assert(r4.valid == false);
    
    /* Test 5: Check validation count */
    const envelope_state_t* state = envelope_get_state();
    assert(state->envelopes_validated == 4);
    
    printf("  PASS\n");
    return 0;
}
