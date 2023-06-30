success=0
fail=0
counter=0
difference=""

flags=(
    "v"
    "c"
    "l"
    "n"
    "h"
    "o"
)

tests=(
    "is FLAGS 1.txt"
    "is -i -s 1.txt nofile.txt FLAGS"
    "-e is FLAGS -e null 2.txt"
    "-ie is -e null 2.txt FLAGS 1.txt nofile.txt"
    "-ie is FLAGS -se null 2.txt 2.txt nofile.txt -f 3.txt"
    "ntempl -ie extended 2.txt 3.txt FLAGS"
    "-estring FLAGS 3.txt"
    "FLAGS -isf 3.txt 1.txt 2.txt"
    "-f non.txt 1.txt FLAGS 2.txt"
)

run_test() {
    param=$(echo "$@" | sed "s/FLAGS/$var/")
    ./s21_grep $param > s21_grep.log
    grep $param > grep.log
    difference="$(diff -s s21_grep.log grep.log)"
    let "counter++"
    if [ "$difference" == "Файлы s21_grep.log и grep.log идентичны" ]
    then
        (( success++ ))
       echo "$fail $success $counter SUCCESS $param"
    else
        (( fail++ ))
        echo "FAILED ./s21_grep $param"
    fi
    rm -rf s21_grep.log grep.log
}

echo "Test №1: 1 parameters"
for var1 in "${flags[@]}"
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        run_test "$i"
    done
done

echo "Test №2: 2 parameters"
for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1 -$var2"
                run_test "$i"
            done
        fi
    done
done

echo "Test №3: 3 parameters"
for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        for var3 in "${flags[@]}"
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1 -$var2 -$var3"
                    run_test "$i"
                done
            fi
        done
    done
done

echo "Test №4: 4 parameters"
for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        for var3 in "${flags[@]}"
        do
            for var4 in "${flags[@]}"
            do
                if [ $var1 != $var2 ] && [ $var2 != $var3 ] \
                && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
                && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                then
                    for i in "${tests[@]}"
                    do
                        var="-$var1 -$var2 -$var3 -$var4"
                        run_test "$i"
                    done
                fi
            done
        done
    done
done

echo "Test №5: double parameters"
for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1$var2"
                run_test "$i"
            done
        fi
    done
done

echo "Test №6: triple parameters"
for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        for var3 in "${flags[@]}"
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1$var2$var3"
                    run_test "$i"
                done
            fi
        done
    done
done
echo "number of fail: $fail\033[0m"
echo "number of success: $success\033[0m"
echo "number of tests: $counter"
