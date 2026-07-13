/**
 * @file compiler.h
 * @brief Compiler Header
 * 
 * This header defines the interface for the Compiler.
 * The Compiler provides constraint validation and law enforcement.
 * 
 * Authority: auth-compiler (scaffolded, not granted)
 * Receipt emission: DISABLED
 */

#ifndef COMPILER_H
#define COMPILER_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Constraint types from law-to-constraint translation
 */
typedef enum {
    CONSTRAINT_PAIR_CONSTRUCTION = 0,   /* pair-cons8 */
    CONSTRAINT_PAIR_CAR_ACCESS = 1,     /* pair-car8 */
    CONSTRAINT_PAIR_CDR_ACCESS = 2,     /* pair-cdr8 */
    CONSTRAINT_KERNEL_DELTA16 = 3,      /* kernel-delta16 */
    CONSTRAINT_ATOMIC_DELTA16 = 4,      /* atomic-delta16 */
    CONSTRAINT_EVAL_PRIMITIVE_CAR = 5,  /* eval-primitive-car */
    CONSTRAINT_EVAL_PRIMITIVE_CDR = 6,  /* eval-primitive-cdr */
    CONSTRAINT_EVAL_PRIMITIVE_CONS = 7  /* eval-primitive-cons */
} constraint_type_t;

/**
 * @brief Constraint validation result
 */
typedef struct {
    bool valid;
    constraint_type_t type;
    const char* message;
} constraint_result_t;

/**
 * @brief Compiler initialization state
 */
typedef struct {
    bool initialized;
    uint64_t constraints_enforced;
    uint64_t violations_detected;
} compiler_state_t;

/**
 * @brief Initialize the compiler
 * @return 0 on success, non-zero on failure
 */
int compiler_init(void);

/**
 * @brief Validate a constraint
 * @param type The constraint type to validate
 * @param value The value to validate against the constraint
 * @return The validation result
 */
constraint_result_t compiler_validate_constraint(constraint_type_t type, uint64_t value);

/**
 * @brief Enforce a law
 * @param law_id The law ID to enforce
 * @param value The value to check against the law
 * @return 0 if law is satisfied, non-zero if violated
 */
int compiler_enforce_law(const char* law_id, uint64_t value);

/**
 * @brief Validate a receipt (stub)
 * @param receipt The receipt to validate
 * @return true if valid, false if invalid
 * 
 * NOTE: Receipt validation is a stub.
 * Actual receipt validation requires runtime receipt authority.
 */
bool compiler_validate_receipt_stub(uint64_t receipt);

/**
 * @brief Get the current compiler state
 * @return Pointer to the compiler state
 */
const compiler_state_t* compiler_get_state(void);

/**
 * @brief Check if constraint enforcement is enabled
 * @return true if enabled, false if disabled
 * 
 * NOTE: Constraint enforcement is currently DISABLED by build contract.
 * This function will return false until authority is granted.
 */
bool compiler_enforcement_enabled(void);

#endif /* COMPILER_H */
