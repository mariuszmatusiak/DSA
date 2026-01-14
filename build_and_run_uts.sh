rm -rf output
cmake -S . -B output -DCMAKE_BUILD_TYPE=Debug && cmake --build output
# run_uts
./output/utils/DSA_Utils_Lib_Tests
./output/structures/DSA_Structures_Lib_Tests
./output/algorithms/DSA_Algorithms_Lib_Tests
./output/leetcode_solutions/DSA_LeetCode_Lib_Tests
./output/modern_cpp/DSA_Modern_cpp
