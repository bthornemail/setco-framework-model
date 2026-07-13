# Envelope-Plan Construction Index

Target: setco-framework-model
Total plans: 6

## Summary

| Receipt Stages | Count |
|----------------|-------|
| 5 | 4 |
| 6 | 2 |

## Envelope Plans

### autonomous-world-live-transport-adapter-court.omilisp

- **Plan ID:** env-plan-132f4422c0ba
- **Source SID:** autonomous-world-live-transport-adapter-court
- **Receipt Chain:** identity=pending; projection=pending; transport-plan=pending; transport-event=pending; processing=pending
- **Receipt Stages:** 5
- **Required Fields:** envelope-version, envelope-type, identity-hash, projection-target, transport-origin, transport-destination, timestamp, receipt-hash, authority-signature
- **Requires Runtime Receipt:** True
- **Status:** planned
- **Recommended Next:** Pass 9H: envelope construction

### autonomous-world-merge-reconciliation-court.omilisp

- **Plan ID:** env-plan-41158c9571f6
- **Source SID:** autonomous-world-merge-reconciliation-court
- **Receipt Chain:** identity=pending; projection=pending; merge-candidate=pending; conflict=pending; admission-decision=pending; merged-world=pending
- **Receipt Stages:** 6
- **Required Fields:** envelope-version, envelope-type, identity-hash, projection-target, merge-source, merge-target, timestamp, receipt-hash, authority-signature
- **Requires Runtime Receipt:** True
- **Status:** planned
- **Recommended Next:** Pass 9H: envelope construction

### autonomous-world-package-sync-court.omilisp

- **Plan ID:** env-plan-858a55cc69de
- **Source SID:** autonomous-world-package-sync-court
- **Receipt Chain:** identity=pending; projection=pending; package=pending; history-edge=pending; snapshot=pending; local-admission=pending
- **Receipt Stages:** 6
- **Required Fields:** envelope-version, envelope-type, identity-hash, projection-target, package-id, timestamp, receipt-hash, authority-signature
- **Requires Runtime Receipt:** True
- **Status:** planned
- **Recommended Next:** Pass 9H: envelope construction

### autonomous-world-peer-exchange-protocol.omilisp

- **Plan ID:** env-plan-f69795b874f8
- **Source SID:** autonomous-world-peer-exchange-protocol
- **Receipt Chain:** identity=pending; projection=pending; peer=pending; offer=pending; exchange=pending
- **Receipt Stages:** 5
- **Required Fields:** envelope-version, envelope-type, identity-hash, projection-target, peer-id, offer-hash, timestamp, receipt-hash, authority-signature
- **Requires Runtime Receipt:** True
- **Status:** planned
- **Recommended Next:** Pass 9H: envelope construction

### autonomous-world-transport-repair-court.omilisp

- **Plan ID:** env-plan-bd4b45687087
- **Source SID:** autonomous-world-transport-repair-court
- **Receipt Chain:** identity=pending; projection=pending; repair-request=pending; repair-payload=pending; repair-result=pending
- **Receipt Stages:** 5
- **Required Fields:** envelope-version, envelope-type, identity-hash, projection-target, repair-target, repair-payload-hash, timestamp, receipt-hash, authority-signature
- **Requires Runtime Receipt:** True
- **Status:** planned
- **Recommended Next:** Pass 9H: envelope construction

### autonomous-world-transport-replay-court.omilisp

- **Plan ID:** env-plan-e0cf17b1e8d2
- **Source SID:** autonomous-world-transport-replay-court
- **Receipt Chain:** identity=pending; projection=pending; transport-log=pending; replay-entry=pending; replay=pending
- **Receipt Stages:** 5
- **Required Fields:** envelope-version, envelope-type, identity-hash, projection-target, transport-log-id, replay-entry-hash, timestamp, receipt-hash, authority-signature
- **Requires Runtime Receipt:** True
- **Status:** planned
- **Recommended Next:** Pass 9H: envelope construction

