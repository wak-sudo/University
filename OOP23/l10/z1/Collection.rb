class Collection # Stos z dowolnym dostępem
    def initialize
        @stack = Array.new(0)
    end
    def push(el)
        @stack.push(el)
    end
    def get(i)
        if(i >= @stack.length or i < 0)
            fail "Invalid index"
        end
        @stack[i]
    end
    def length
        @stack.length
    end
    def swap(i, j)
        if (i >= @stack.length or i < 0 or j >= @stack.length or j < 0)
            fail "Invalid index"
        end
        @stack[i], @stack[j] = @stack[j], @stack[i]
    end
    def pop
        if(0 >= @stack.length)
            fail "Stack is already empty"
        end
        @stack.pop
    end
    def top
        if(0 >= @stack.length)
            fail "Stack is already empty"
        end
        @stack.last
    end
    def to_s
        @stack.join(" ")
    end
    def clear
        @stack.clear
    end
    def rand(number, topRange)
        i = 0
        while i < number
            push(Random.rand(topRange))
            i += 1
        end
        nil
    end
end