#FSOARES
# test 1
./pipex infile.txt cat wc /dev/stdout
# test 3
./pipex infile.txt 'sed "s/And/But/"' 'grep But' /dev/stdout
# test 4
./pipex infile.txt 'sed "s/And/But/"' "awk '{count++} END {print count}'" /dev/stdout
# test 5
./pipex infile.txt 'sed "s/And/But/"' 'awk "{count++} END {print count}"' /dev/stdout
# test 6
./pipex infile.txt "sed s/And/But/" "awk '{count++} END {printf \"count: %i\", count}'" /dev/stdout
# test 7
./pipex infile.txt 'sed "s/And/But/"' "awk '{count++} END {printf \"count: %i\", count}'" /dev/stdout
# test 8
./pipex infile.txt "./script.sh" 'wc' /dev/stdout
# test 9
./pipex infile.txt './script space.sh' 'wc' /dev/stdout
# test 10
./pipex infile.txt './script\"quote.sh' 'wc' /dev/stdout
# test 10.2
./pipex infile.txt './script"quote.sh' 'wc' /dev/stdout
# test 11
./pipex infile.txt "'./script space.sh'" 'wc' /dev/stdout
# test 13
./pipex no_in 'cat' 'wc' /dev/stdout
# test 14
./pipex infile.txt 'hello' 'wc' /dev/stdout
# test 15
./pipex infile.txt 'wc' 'hello' /dev/stdout
# test 16
./pipex no_r_perm 'cat' 'wc' /dev/stdout
# test 17
./pipex infile.txt 'cat' 'wc' no_w_perm
# test 18
./pipex infile.txt './no_x_script.sh' 'wc' /dev/stdout
# test 19
./pipex infile.txt 'cat' './no_x_script.sh' /dev/stdout
# test 20
./pipex infile.txt './middle_fail.sh' 'wc' /dev/stdout
# test 21
./pipex infile.txt 'cat' './middle_fail.sh' /dev/stdout
# test 22 avec path=""
./pipex infile.txt './script.sh' './script.sh' /dev/stdout
# test 23 avec path=""
./pipex infile.txt 'cat' 'wc' /dev/stdout
# test 26
./pipex infile.txt 'cat' './script.sh' /dev/stdout
# test 27 avec path=f"{self.tests_dir}:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
./pipex infile.txt 'cat' 'uname' /dev/stdout
# test 28 avec path=f"/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:{self.tests_dir}"
./pipex infile.txt 'cat' 'uname' /dev/stdout
# test 29 avec path=f"/bin"
./pipex infile.txt 'cat' 'wc' /dev/stdout
# test 31
./pipex infile.txt 'subdir/script.sh' 'wc' /dev/stdout

#TESTS SLEEP
# test 1
time ./pipex infile.txt 'sleep 9' 'sleep 5' /dev/stdout