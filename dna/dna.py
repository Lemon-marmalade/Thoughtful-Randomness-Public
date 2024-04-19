import csv
import sys


def main():

    # TODO: Check for command-line usage

    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py database.csv sequence.csv")
    else:
    # TODO: Read database file into a variable
            database = []
            with open(sys.argv[1], 'r') as file:
                reader = csv.DictReader(file)
                for row in reader:
                    database.append(row)
    # TODO: Read DNA sequence file into a variable
            with open(sys.argv[2], 'r') as file:
                dna = file.read
    # TODO: Find longest match of each STR in DNA sequence
                #compile a list of STRs from the first row of database excluding first element
            STRs = list(database[0].keys())[1:]
            #create dictionary for longest number of repeats for each str
            longest = {}
            for STR in STRs:
                #find longest match
                longest[STR] = longest_match(dna, STR)
    # TODO: Check database for matching profiles
            #for each person in the database, check for each STR if the longest is a match
            for person in database:
                match = 0
                for STR in STRS:
                    if int(person[STR]) == longest[STR]:
                        match += 1
                #if all STRs match the longest of the given dna sequence, print name
                if match == len(STRS):
                    print(f"{person["name"]})
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
