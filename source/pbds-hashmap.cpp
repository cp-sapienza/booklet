#include <ext/pb_ds/assoc_container.hpp>
struct chash {
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	ll operator()(ll x) const { return __builtin_bswap64(x*C); }
};
template<typename Value>
using hashmap = __gnu_pbds::gp_hash_table<ll,Value,chash>;