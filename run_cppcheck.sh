# run_sca.sh
rm -rf output/static_analysis
mkdir -p output/static_analysis
cppcheck --std=c++20 --enable=warning --enable=style --enable=information --check-level=exhaustive --language=c++ --cppcheck-build-dir=output/static_analysis --addon=misra --file-list=cppcheck/src_list.cfg --includes-file=cppcheck/inc_list.cfg --checkers-report=output/static_analysis/checkers_report.txt
