# Critical Runtime-Boundary Review

Target: setco-framework-model
Total critical candidates: 16

## Summary

| Action | Count |
|--------|-------|
| legacy-module-normalization-required | 9 |
| envelope-plan-required | 6 |
| receipt-authority-required | 1 |

| Recommended Next Pass | Count |
|----------------------|-------|
| Pass 9F: legacy-module normalization | 9 |
| Pass 9G: envelope-plan construction | 6 |
| Pass 9E: law-to-constraint translation | 1 |

## Detailed Reviews

### 1. autonomous-world-live-transport-adapter-court.omilisp

- **Title:** Autonomous World Live Transport Adapter Court
- **SID:** autonomous-world-live-transport-adapter-court
- **Kind:** world.live-transport-adapter-court
- **Reason:** extended-receipt-chain
- **Classification:** requires-envelope
- **Action:** envelope-plan-required
- **Why Critical:** Extended receipt chain with 5 stages — requires envelope planning
- **Required Normalization:** Receipt chain must be mapped to envelope construction
- **Envelope Planning Required:** True
- **Receipt Authority Required:** False
- **Legacy Module Normalization Required:** False
- **Recommended Next Pass:** Pass 9G: envelope-plan construction
- **Receipts:** identity=pending; projection=pending; transport-plan=pending; transport-event=pending; processing=pending

### 2. autonomous-world-merge-reconciliation-court.omilisp

- **Title:** Autonomous World Merge / Reconciliation Court
- **SID:** autonomous-world-merge-reconciliation-court
- **Kind:** world.merge-reconciliation-court
- **Reason:** extended-receipt-chain
- **Classification:** requires-envelope
- **Action:** envelope-plan-required
- **Why Critical:** Extended receipt chain with 6 stages — requires envelope planning
- **Required Normalization:** Receipt chain must be mapped to envelope construction
- **Envelope Planning Required:** True
- **Receipt Authority Required:** False
- **Legacy Module Normalization Required:** False
- **Recommended Next Pass:** Pass 9G: envelope-plan construction
- **Receipts:** identity=pending; projection=pending; merge-candidate=pending; conflict=pending; admission-decision=pending; merged-world=pending

### 3. autonomous-world-package-sync-court.omilisp

- **Title:** Autonomous World Package Sync Court
- **SID:** autonomous-world-package-sync-court
- **Kind:** world.package-sync-court
- **Reason:** extended-receipt-chain
- **Classification:** requires-envelope
- **Action:** envelope-plan-required
- **Why Critical:** Extended receipt chain with 6 stages — requires envelope planning
- **Required Normalization:** Receipt chain must be mapped to envelope construction
- **Envelope Planning Required:** True
- **Receipt Authority Required:** False
- **Legacy Module Normalization Required:** False
- **Recommended Next Pass:** Pass 9G: envelope-plan construction
- **Receipts:** identity=pending; projection=pending; package=pending; history-edge=pending; snapshot=pending; local-admission=pending

### 4. autonomous-world-peer-exchange-protocol.omilisp

- **Title:** Autonomous World Peer Exchange Protocol
- **SID:** autonomous-world-peer-exchange-protocol
- **Kind:** world.peer-exchange-protocol
- **Reason:** extended-receipt-chain
- **Classification:** requires-envelope
- **Action:** envelope-plan-required
- **Why Critical:** Extended receipt chain with 5 stages — requires envelope planning
- **Required Normalization:** Receipt chain must be mapped to envelope construction
- **Envelope Planning Required:** True
- **Receipt Authority Required:** False
- **Legacy Module Normalization Required:** False
- **Recommended Next Pass:** Pass 9G: envelope-plan construction
- **Receipts:** identity=pending; projection=pending; peer=pending; offer=pending; exchange=pending

### 5. autonomous-world-transport-repair-court.omilisp

- **Title:** Autonomous World Transport Repair Court
- **SID:** autonomous-world-transport-repair-court
- **Kind:** world.transport-repair-court
- **Reason:** extended-receipt-chain
- **Classification:** requires-envelope
- **Action:** envelope-plan-required
- **Why Critical:** Extended receipt chain with 5 stages — requires envelope planning
- **Required Normalization:** Receipt chain must be mapped to envelope construction
- **Envelope Planning Required:** True
- **Receipt Authority Required:** False
- **Legacy Module Normalization Required:** False
- **Recommended Next Pass:** Pass 9G: envelope-plan construction
- **Receipts:** identity=pending; projection=pending; repair-request=pending; repair-payload=pending; repair-result=pending

### 6. autonomous-world-transport-replay-court.omilisp

- **Title:** Autonomous World Transport Replay Court
- **SID:** autonomous-world-transport-replay-court
- **Kind:** world.transport-replay-court
- **Reason:** extended-receipt-chain
- **Classification:** requires-envelope
- **Action:** envelope-plan-required
- **Why Critical:** Extended receipt chain with 5 stages — requires envelope planning
- **Required Normalization:** Receipt chain must be mapped to envelope construction
- **Envelope Planning Required:** True
- **Receipt Authority Required:** False
- **Legacy Module Normalization Required:** False
- **Recommended Next Pass:** Pass 9G: envelope-plan construction
- **Receipts:** identity=pending; projection=pending; transport-log=pending; replay-entry=pending; replay=pending

### 7. canon-operational/envelope-bitboard.omilisp

- **Title:** 
- **SID:** 
- **Kind:** 
- **Reason:** no-sid-legacy-module
- **Classification:** legacy-runtime-module
- **Action:** legacy-module-normalization-required
- **Why Critical:** Legacy omi-module form without SID — may contain runtime-boundary code
- **Required Normalization:** Legacy module must be parsed and classified
- **Envelope Planning Required:** False
- **Receipt Authority Required:** False
- **Legacy Module Normalization Required:** True
- **Recommended Next Pass:** Pass 9F: legacy-module normalization

### 8. canon-operational/omicron-receipt.omilisp

- **Title:** 
- **SID:** 
- **Kind:** 
- **Reason:** no-sid-legacy-module
- **Classification:** legacy-runtime-module
- **Action:** legacy-module-normalization-required
- **Why Critical:** Legacy omi-module form without SID — may contain runtime-boundary code
- **Required Normalization:** Legacy module must be parsed and classified
- **Envelope Planning Required:** False
- **Receipt Authority Required:** False
- **Legacy Module Normalization Required:** True
- **Recommended Next Pass:** Pass 9F: legacy-module normalization

### 9. canon-operational/omiom.omilisp

- **Title:** 
- **SID:** 
- **Kind:** 
- **Reason:** no-sid-legacy-module
- **Classification:** legacy-runtime-module
- **Action:** legacy-module-normalization-required
- **Why Critical:** Legacy omi-module form without SID — may contain runtime-boundary code
- **Required Normalization:** Legacy module must be parsed and classified
- **Envelope Planning Required:** False
- **Receipt Authority Required:** False
- **Legacy Module Normalization Required:** True
- **Recommended Next Pass:** Pass 9F: legacy-module normalization

### 10. canon-operational/orbit.omilisp

- **Title:** 
- **SID:** 
- **Kind:** 
- **Reason:** no-sid-legacy-module
- **Classification:** legacy-runtime-module
- **Action:** legacy-module-normalization-required
- **Why Critical:** Legacy omi-module form without SID — may contain runtime-boundary code
- **Required Normalization:** Legacy module must be parsed and classified
- **Envelope Planning Required:** False
- **Receipt Authority Required:** False
- **Legacy Module Normalization Required:** True
- **Recommended Next Pass:** Pass 9F: legacy-module normalization

### 11. canon-operational/semantic-lattice.omilisp

- **Title:** 
- **SID:** 
- **Kind:** 
- **Reason:** no-sid-legacy-module
- **Classification:** legacy-runtime-module
- **Action:** legacy-module-normalization-required
- **Why Critical:** Legacy omi-module form without SID — may contain runtime-boundary code
- **Required Normalization:** Legacy module must be parsed and classified
- **Envelope Planning Required:** False
- **Receipt Authority Required:** False
- **Legacy Module Normalization Required:** True
- **Recommended Next Pass:** Pass 9F: legacy-module normalization

### 12. canon-operational/sense-pg.omilisp

- **Title:** 
- **SID:** 
- **Kind:** 
- **Reason:** no-sid-legacy-module
- **Classification:** legacy-runtime-module
- **Action:** legacy-module-normalization-required
- **Why Critical:** Legacy omi-module form without SID — may contain runtime-boundary code
- **Required Normalization:** Legacy module must be parsed and classified
- **Envelope Planning Required:** False
- **Receipt Authority Required:** False
- **Legacy Module Normalization Required:** True
- **Recommended Next Pass:** Pass 9F: legacy-module normalization

### 13. metatron-operational/metatron-witness.omilisp

- **Title:** 
- **SID:** 
- **Kind:** 
- **Reason:** no-sid-legacy-module
- **Classification:** legacy-runtime-module
- **Action:** legacy-module-normalization-required
- **Why Critical:** Legacy omi-module form without SID — may contain runtime-boundary code
- **Required Normalization:** Legacy module must be parsed and classified
- **Envelope Planning Required:** False
- **Receipt Authority Required:** False
- **Legacy Module Normalization Required:** True
- **Recommended Next Pass:** Pass 9F: legacy-module normalization

### 14. omnicron-operational/atomic-kernel.omilisp

- **Title:** 
- **SID:** 
- **Kind:** 
- **Reason:** no-sid-legacy-module
- **Classification:** legacy-runtime-module
- **Action:** legacy-module-normalization-required
- **Why Critical:** Legacy omi-module form without SID — may contain runtime-boundary code
- **Required Normalization:** Legacy module must be parsed and classified
- **Envelope Planning Required:** False
- **Receipt Authority Required:** False
- **Legacy Module Normalization Required:** True
- **Recommended Next Pass:** Pass 9F: legacy-module normalization

### 15. omnicron-operational/pair-machine.omilisp

- **Title:** 
- **SID:** 
- **Kind:** 
- **Reason:** no-sid-legacy-module
- **Classification:** legacy-runtime-module
- **Action:** legacy-module-normalization-required
- **Why Critical:** Legacy omi-module form without SID — may contain runtime-boundary code
- **Required Normalization:** Legacy module must be parsed and classified
- **Envelope Planning Required:** False
- **Receipt Authority Required:** False
- **Legacy Module Normalization Required:** True
- **Recommended Next Pass:** Pass 9F: legacy-module normalization

### 16. omnicron-pair-machine.omilisp

- **Title:** Omnicron Pair Machine Port
- **SID:** omnicron-pair-machine
- **Kind:** runtime.pair-machine-declaration
- **Reason:** has-laws
- **Classification:** requires-receipt-authority
- **Action:** receipt-authority-required
- **Why Critical:** Contains runtime laws that require receipt authority
- **Required Normalization:** Laws must be translated to compiler constraints or runtime rules
- **Envelope Planning Required:** False
- **Receipt Authority Required:** True
- **Legacy Module Normalization Required:** False
- **Recommended Next Pass:** Pass 9E: law-to-constraint translation
- **Laws:** pair-cons8, pair-car8, pair-cdr8, kernel-delta16, atomic-delta16, eval-primitive-car, eval-primitive-cdr, eval-primitive-cons

