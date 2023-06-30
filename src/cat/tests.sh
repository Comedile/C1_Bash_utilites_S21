
echo cat bflag and number-nonblank
diff <(cat -b test_files/test_1_cat.txt) <(./s21_cat -b test_files/test_1_cat.txt) -s
diff <(cat -b test_files/test_2_cat.txt) <(./s21_cat -b test_files/test_2_cat.txt) -s
diff <(cat -b test_files/test_3_cat.txt) <(./s21_cat -b test_files/test_3_cat.txt) -s
diff <(cat --number-nonblank test_files/test_4_cat.txt) <(./s21_cat --number-nonblank test_files/test_4_cat.txt) -s
diff <(cat --number-nonblank test_files/test_5_cat.txt) <(./s21_cat --number-nonblank test_files/test_5_cat.txt) -s
diff <(cat --number-nonblank test_files/test_6_cat.txt) <(./s21_cat --number-nonblank test_files/test_6_cat.txt) -s
echo cat eflag
diff <(cat -e "test_files/test_1_cat.txt") <(./s21_cat -e "test_files/test_1_cat.txt") -s
diff <(cat -e "test_files/test_2_cat.txt") <(./s21_cat -e "test_files/test_2_cat.txt") -s
diff <(cat -e "test_files/test_3_cat.txt") <(./s21_cat -e "test_files/test_3_cat.txt") -s
diff <(cat -e "test_files/test_4_cat.txt") <(./s21_cat -e "test_files/test_4_cat.txt") -s
diff <(cat -e "test_files/test_5_cat.txt") <(./s21_cat -e "test_files/test_5_cat.txt") -s
diff <(cat -e "test_files/test_6_cat.txt") <(./s21_cat -e "test_files/test_6_cat.txt") -s
echo cat nflag and number-flag
diff <(cat -n "test_files/test_1_cat.txt") <(./s21_cat -n "test_files/test_1_cat.txt") -s
diff <(cat -n "test_files/test_2_cat.txt") <(./s21_cat -n "test_files/test_2_cat.txt") -s
diff <(cat -n "test_files/test_3_cat.txt") <(./s21_cat -n "test_files/test_3_cat.txt") -s
diff <(cat --number "test_files/test_4_cat.txt") <(./s21_cat --number "test_files/test_4_cat.txt") -s
diff <(cat --number "test_files/test_5_cat.txt") <(./s21_cat --number "test_files/test_5_cat.txt") -s
diff <(cat --number "test_files/test_6_cat.txt") <(./s21_cat --number "test_files/test_6_cat.txt") -s
echo cat sflag and squeeze-blank
diff <(cat -s "test_files/test_1_cat.txt") <(./s21_cat -s "test_files/test_1_cat.txt") -s
diff <(cat -s "test_files/test_2_cat.txt") <(./s21_cat -s "test_files/test_2_cat.txt") -s
diff <(cat -s "test_files/test_3_cat.txt") <(./s21_cat -s "test_files/test_3_cat.txt") -s
diff <(cat --squeeze-blank "test_files/test_4_cat.txt") <(./s21_cat --squeeze-blank "test_files/test_4_cat.txt") -s
diff <(cat --squeeze-blank "test_files/test_5_cat.txt") <(./s21_cat --squeeze-blank "test_files/test_5_cat.txt") -s
diff <(cat --squeeze-blank "test_files/test_6_cat.txt") <(./s21_cat --squeeze-blank "test_files/test_6_cat.txt") -s
echo cat tflag
diff <(cat -t "test_files/test_1_cat.txt") <(./s21_cat -t "test_files/test_1_cat.txt") -s
diff <(cat -t "test_files/test_2_cat.txt") <(./s21_cat -t "test_files/test_2_cat.txt") -s
diff <(cat -t "test_files/test_3_cat.txt") <(./s21_cat -t "test_files/test_3_cat.txt") -s
diff <(cat -t "test_files/test_4_cat.txt") <(./s21_cat -t "test_files/test_4_cat.txt") -s
diff <(cat -t "test_files/test_5_cat.txt") <(./s21_cat -t "test_files/test_5_cat.txt") -s
diff <(cat -t "test_files/test_6_cat.txt") <(./s21_cat -t "test_files/test_6_cat.txt") -s
echo cat no flag
diff <(cat "test_files/test_1_cat.txt" -n) <(./s21_cat "test_files/test_1_cat.txt" -n) -s
diff <(cat "test_files/test_2_cat.txt" -n) <(./s21_cat "test_files/test_2_cat.txt" -n) -s
diff <(cat "test_files/test_3_cat.txt" -n) <(./s21_cat "test_files/test_3_cat.txt" -n) -s
diff <(cat "test_files/test_4_cat.txt" -n) <(./s21_cat "test_files/test_4_cat.txt" -n) -s
diff <(cat "test_files/test_5_cat.txt" -n) <(./s21_cat "test_files/test_5_cat.txt" -n) -s
diff <(cat "test_files/test_6_cat.txt" -n) <(./s21_cat "test_files/test_6_cat.txt" -n) -s
echo cat Tflag
diff <(cat -T "test_files/test_1_cat.txt") <(./s21_cat -T "test_files/test_1_cat.txt") -s
diff <(cat -T "test_files/test_2_cat.txt") <(./s21_cat -T "test_files/test_2_cat.txt") -s
diff <(cat -T "test_files/test_3_cat.txt") <(./s21_cat -T "test_files/test_3_cat.txt") -s
diff <(cat -T "test_files/test_4_cat.txt") <(./s21_cat -T "test_files/test_4_cat.txt") -s
diff <(cat -T "test_files/test_5_cat.txt") <(./s21_cat -T "test_files/test_5_cat.txt") -s
diff <(cat -T "test_files/test_6_cat.txt") <(./s21_cat -T "test_files/test_6_cat.txt") -s
echo cat Eflag
diff <(cat -E "test_files/test_1_cat.txt") <(./s21_cat -E "test_files/test_1_cat.txt") -s
diff <(cat -E "test_files/test_2_cat.txt") <(./s21_cat -E "test_files/test_2_cat.txt") -s
diff <(cat -E "test_files/test_3_cat.txt") <(./s21_cat -E "test_files/test_3_cat.txt") -s
diff <(cat -E "test_files/test_4_cat.txt") <(./s21_cat -E "test_files/test_4_cat.txt") -s
diff <(cat -E "test_files/test_5_cat.txt") <(./s21_cat -E "test_files/test_5_cat.txt") -s
diff <(cat -E "test_files/test_6_cat.txt") <(./s21_cat -E "test_files/test_6_cat.txt") -s