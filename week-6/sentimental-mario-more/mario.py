def main():
    n = get_height()
    print_blocks(n)


def print_blocks(n):
    for i in range(1, n+1):
        print(" " * (n-i), end="")
        print("#" * i, end="")
        print(" " * 2, end="")
        print("#" * i)


def get_height():
    while True:
        try:
            n = int(input("Height: "))
            if n >= 1 and n <= 8:
                return n

        except:
            continue

        
if __name__ == "__main__":
    main()
