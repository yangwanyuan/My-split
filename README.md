# My-split

1. build the my-split with
    $make

2. touch log.file with (if you not have a log sample)
    $ for ((i=0; i<100; i++)); do `echo aaaaaaaaa >> test.log` ; done

3. start to use my-split:
    $ ./my-split test.log 100

4. clean env
    $ make clean
