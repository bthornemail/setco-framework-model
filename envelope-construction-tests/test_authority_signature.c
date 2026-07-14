/**
 * @file test_authority_signature.c
 * @brief Test authority signature verification (Pass 17)
 */

#include <stdio.h>
#include <assert.h>
#include "../envelope-construction.h"

int main(void) {
    printf("Test: authority_signature_test\n");
    
    /* Initialize envelope construction */
    int result = envelope_init();
    assert(result == 0);
    
    /* Test 1: Construct envelope with authority fields */
    envelope_construct_result_t r0 = envelope_construct(0x0001, 0x01, 0x01, 0x0001, 0x0001);
    assert(r0.success == true);
    
    /* Test 2: Validate provenance field */
    envelope_result_t r1 = envelope_validate_field(FIELD_PROVENANCE, 0x0001);
    assert(r1.valid == true);
    
    /* Test 3: Validate steps field */
    envelope_result_t r2 = envelope_validate_field(FIELD_STEPS, 0x01);
    assert(r2.valid == true);
    
    /* Test 4: Validate LL field */
    envelope_result_t r3 = envelope_validate_field(FIELD_LL, 0x01);
    assert(r3.valid == true);
    
    /* Test 5: Validate NN field */
    envelope_result_t r4 = envelope_validate_field(FIELD_NN, 0x0001);
    assert(r4.valid == true);
    
    /* Test 6: Validate MM field */
    envelope_result_t r5 = envelope_validate_field(FIELD_MM, 0x0001);
    assert(r5.valid == true);
    
    printf("  PASS\n");
    return 0;
}
