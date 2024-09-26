object Basic extends App
{
    def sortUgly(xs: List[Int]): List[Int] = 
    {
        val tempArr = xs.toArray
        quicksortUgly(tempArr, 0, tempArr.size-1)
        tempArr.toList
    }

    def swap(arr: Array[Int], i : Int, j : Int) : Unit = {
        val temp = arr(i)
        arr(i) = arr(j)
        arr(j) = temp
    }

    def quicksortUgly(xs: Array[Int], lo: Int, hi: Int): Unit = {
        if (lo < hi && lo >= 0)
        {
            val p = partitionUgly(xs, lo, hi)
            quicksortUgly(xs, lo, p-1)
            quicksortUgly(xs, p+1, hi)
        }
    }

    def partitionUgly(arr: Array[Int], low: Int, high: Int): Int = {
        val pivot = arr(high)
        var i = low - 1
        var j = low
        if(j <= high-1)
        {
            do
            {
                if (arr(j) <= pivot) {
                    i += 1
                    swap(arr, i, j)
                }
                j += 1
            }
            while(j <= high-1)
        }
        swap(arr, i+1, high)
        i + 1
    }

    val unsorted = List(64, 25, 12, 22, 11)
    println(sortUgly(unsorted))

    def sort(xs: List[Int]): List[Int] = 
    {
        quciksort(xs.toArray).toList
    }

    def quciksort(arr: Array[Int]) : Array[Int] = {
        if (arr.length <= 1) arr
        else
        {
            val pivot = arr(arr.size / 2)
            Array.concat(
                quciksort(arr.filter(_ < pivot)),
                arr.filter(_ == pivot),
                quciksort(arr.filter(_ > pivot))
            )
        }
    }

    println(sort(unsorted))
}