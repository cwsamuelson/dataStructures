Universally Unique IDentifier
=============================

## Resources
- [RFC-4122](https://datatracker.ietf.org/doc/html/rfc4122)
- [uuid tools](https://www.uuidtools.com/uuid-versions-explained)

## V1
Based on current time and system MAC address.  Time is nanoseconds since
15 Oct 1582.  In practice a random MAC may be used, so as to not reveal the real
node's MAC.  I should think this random MAC should be consistent, however.

Because of the data sources used to generate them, a UUID-v1 can be decoded to
reveal the time and MAC used to generate it.

## V2
Not widely used, due to several flaws.  Uses timestamp, MAC address, and user ID
or group ID.  Traits like the MAC, and user identifiers reduce possible
randomness of a UUID-v2.  UUID-v2 timestamp only increments every ~7 minutes,
which also significantly limits how many possible UUIDs that are available
within a given 7 minute period (64!?).

Because of the data sources used to generate them, a UUID-v2 can be decoded to
reveal the time, MAC, user, and group used to generate it.

## V3 and v5
Generated from a namespace and unique name that are concatenated and hashed.  No random or temporal components are involved.  This makes them deterministic.  V3 is based on MD5, and V5 is based on SHA-1; SHA-1 must be truncated.  Per the spec, there are 4 pre-defined namespaces:
- DNS: 6ba7b810-9dad-11d1-80b4-00c04fd430c8
- URL: 6ba7b811-9dad-11d1-80b4-00c04fd430c8
- OID: 6ba7b812-9dad-11d1-80b4-00c04fd430c8
- X.500 DN: 6ba7b814-9dad-11d1-80b4-00c04fd430c8

## V4
UUID-V4 is totally randomly generated.  V4 has 2 variants.  V2 is known as 'GUID'.
According to [uuid tools](https://www.uuidtools.com/uuid-versions-explained),
V4 also contains an unofficial variant: Timestamp-first UUIDs, 'Ordered UUIDs',
or COMB (COMBined time-GUID).

### Timestamp-first
Combines timestamp with randomness.

## V7

## Design
Including the timestamp is a valuable trait, because sorting by UUID implies
sorting by creation time.

Including the MAC address helps ensure uniquity between IDs generated at the
same time.

Including user ID etc ensures uniquity even between UDs generated on the same
machine.

Including MAC address or user ID ties the ID to a specific person and machine.
This is sometimes a disadvantage.
