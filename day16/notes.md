memoization
from 1.9 million calls to 1362 for the test input
- checking if all valves are open
- checking the valve we're trying to go to is the valve we just came from, without opening any new valves
- checking the valve we're trying to go to is one of **any** of the valves we came from since the last valve was opened, without opening any new valves
- changed the algorithm completely to only visit the valves that can be opened

still too slow