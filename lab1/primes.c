int main(int argc, char const *argv[]) {
    if(argc > 1) {
        fprintf(2,"argument error");
        exit(1);
    }
    int primes[33];

    for (int i = 0; i < sizeof(primes); i++)
    {
        primes[i] = i + 2;
    }

    prime(primes);


}


//打印素数 并返回过滤后的数组
int* prime(int primes[]) {
    int p = primes[0];

    printf("prime:%d\n",p); //素数

    int count = 0;

    for (int i = 1; i < sizeof(primes); i++)
    {
        if(primes[i] == 0 || primes[i] % p == 0) {
            //不可以放在通往下一站的列车上
            primes[i] = -1;
            continue;
        }

        count++; //记录一下有几个可以乘坐通往下一站的列车
    }

    //准备列车
    int nextPrimes[count];
    //上车
    int index = 0;
    for (int i = 1; i < sizeof(primes); i++)
    {
        if(primes[i] != -1) {
            nextPrimes[index++] = primes[i];
        }
    }

    return nextPrimes;
}







void function() {
    int primes[33];

    for (int i = 0; i < sizeof(primes); i++)
    {
        primes[i] = i + 2;
    }

    int p[2];

    int k = pipe(p);

    if(k < 0) {
        exit(1);
    }

    int pid = fork();

    if(pid > 0) {
        //printf("prime:%d\n",primes[0]); //素数

        int* arr = prime(primes);

        for(int i = 1; i < sizeof(primes);i++){
            write(p[1],i,sizeof(int));
        }

        close(1);
        wait(NULL);

    }else {
        int inbuf[33];

        for(int i = 0; i < sizeof(inbuf); i++) {
            read(p[0],inbuf[i],sizeof(int));
        }

        int* arr = prime(inbuf);


    }
}