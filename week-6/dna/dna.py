import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage:  python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    data = {} 
    STR_list = []
    with open(sys.argv[1], "r") as f:
        reader = csv.DictReader(f)
        for row in reader:
            tmp = []
            for subseq in row.keys():
                if subseq != 'name':
                    if subseq not in STR_list:
                        STR_list.append(subseq)
                    tmp.append(row[subseq])
            data[" ".join(tmp)] = row['name'] 
                
    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as f:
        dna_seq = f.readline() 

    # TODO: Find longest match of each STR in DNA sequence
    profile = " ".join([str(longest_match(dna_seq, subseq)) for subseq in STR_list])
    # TODO: Check database for matching profiles

    if profile in data:
        print(data[profile])
        return
    
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            
            # If there is no match in the substring
            else:
                break
        
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
