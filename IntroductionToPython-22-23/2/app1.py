def szachownica(n, k):
    for i in range(2*n):
        if i % 2 == 0:
            czesc = (k*' ' + k*'#')*n
        else:
            czesc = (k*'#' + k*' ')*n

        for j in range(k):
            print(czesc)

szachownica(4,3)
