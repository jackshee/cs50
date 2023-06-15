def main():
    number = get_number()
    num_list = list(map(int, str(number)))
    if is_valid(num_list):
        if len(num_list) == 15:
            if num_list[0:2] == [3, 4] or num_list[0:2] == [3, 7]:
                print("AMEX")
            else:
                print("INVALID")
        elif len(num_list) == 13 and num_list[0] == 4:
            print("VISA")
        elif len(num_list) == 16:
            if num_list[0] == 4:
                print("VISA")
            elif (num_list[0] == 5) and (num_list[1] in list(range(1, 6))):
                print("MASTERCARD")
            else:
                print("INVALID")
        else:
            print("INVALID")
    else:
        print("INVALID")


def get_number():
    while True:
        try:
            number = int(input("Number: "))
            return number 
        except:
            continue


def is_valid(num_list):

    sum_digit = 0
    for j in range(1, len(num_list) + 1):
        if j % 2 == 0:
            sum_digit += sum(map(int, str(2*num_list[-j])))
        else:
            sum_digit += num_list[-j]

    return sum_digit % 10 == 0


if __name__ == "__main__":
    main()
