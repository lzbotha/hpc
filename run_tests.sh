for ((d=3;d<21;d=d+2))
do
    for ((n=0;n<3;n++))
    do
        optirun --no-xorg ./parallel/tool  $1 output.csv 128 $d | cat >> parallel_results.txt
        optirun --no-xorg ./sequential/tool  $1 output.csv 128 $d | cat >> sequential_results.txt
    done
done

for ((d=3;d<21;d=d+2))
do
    for ((n=0;n<3;n++))
    do
        optirun --no-xorg ./parallel/tool  $1 output.csv 256 $d | cat >> parallel_results.txt
        optirun --no-xorg ./sequential/tool  $1 output.csv 256 $d | cat >> sequential_results.txt
    done
done

for ((d=3;d<21;d=d+2))
do
    for ((n=0;n<3;n++))
    do
        optirun --no-xorg ./parallel/tool  $1 output.csv 512 $d | cat >> parallel_results.txt
        optirun --no-xorg ./sequential/tool  $1 output.csv 512 $d | cat >> sequential_results.txt
    done
done

for ((d=3;d<21;d=d+2))
do
    for ((n=0;n<3;n++))
    do
        optirun --no-xorg ./parallel/tool  $1 output.csv 1024 $d | cat >> parallel_results.txt
        optirun --no-xorg ./sequential/tool  $1 output.csv 1024 $d | cat >> sequential_results.txt
    done
done

for ((d=3;d<21;d=d+2))
do
    for ((n=0;n<3;n++))
    do
        optirun --no-xorg ./parallel/tool  $1 output.csv 2048 $d | cat >> parallel_results.txt
        optirun --no-xorg ./sequential/tool  $1 output.csv 2048 $d | cat >> sequential_results.txt
    done
done

for ((d=3;d<21;d=d+2))
do
    for ((n=0;n<3;n++))
    do
        optirun --no-xorg ./parallel/tool  $1 output.csv 4096 $d | cat >> parallel_results.txt
        optirun --no-xorg ./sequential/tool  $1 output.csv 4096 $d | cat >> sequential_results.txt
    done
done