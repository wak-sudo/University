require_relative "Collection.rb"

# Bubble sort (sort1) średnio wykonuje się w O(n^2)
# Quick Sort (sort2) średnio wykonuje się w O(nlogn)
# Dla małych zbiorów bubble sort będzie szybszy, dla większych szybszy będzie quick sort.
# Dla zastosowań ogólnych można stwierdzić, że quick sort jest szybszy.

class Sorter
    def sort1(kolekcja) # Bubble Sort
        unless kolekcja.kind_of?(Collection)
            fail "Argument nie jest kolekcja"
        end 

        i = 0
        while i < kolekcja.length-1
            j = 0
            while j < kolekcja.length-1-i
                if kolekcja.get(j) > kolekcja.get(j+1)
                    kolekcja.swap(j, j+1)
                end
                j += 1
            end 
            i += 1    
        end
        nil
    end

    def sort2(kolekcja) # Quick Sort
        unless kolekcja.kind_of?(Collection)
            fail "Argument nie jest kolekcja"
        end
        quickSort(kolekcja, 0, kolekcja.length-1)
    end

    private

    def partition(arr, l, r)
        pivot = arr.get(l)
        count = 0
        i  = l + 1
        while i <= r
            if arr.get(i) <= pivot
                count += 1
            end
            i += 1
        end

        pivotIndex = l + count
        arr.swap(pivotIndex, l)
        
        while l < pivotIndex && r > pivotIndex
            while arr.get(l) <= pivot
                l += 1
            end
            while arr.get(r) > pivot
                r -= 1
            end
            if l < pivotIndex && r > pivotIndex
                arr.swap(l, r)
                l += 1
                r -= 1
            end
        end
        pivotIndex
    end

    def quickSort(arr, l, r)
        if l < r
            p = partition(arr, l, r)
            quickSort(arr, l, p-1)
            quickSort(arr, p+1, r)
        end
        nil
    end
end 