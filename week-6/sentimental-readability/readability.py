import re


def main():
    text = input("Text: ")

    # split text into words (words are separated by space) 
    # number of letters per 100 words is (number of letters / number of words * 100) 
    regex = re.compile('[^a-zA-Z]') # the regex pattern matches all non alpha characters
    words = [regex.sub('', word) for word in text.split(' ')]

    # map gets the length of each word which is the number of letters per word, then sum that
    L = sum(map(len, words))/len(words) * 100

    # split text into sentences
    # matches for upper case, then anything that is not either . ! ? followed by one instance of . ! ?
    regex = re.compile(r'([A-Z][^\.!?]*[\.!?])')
    sentences = regex.findall(text)

    S = len(sentences)/len(words) * 100 

    cl_index = 0.0588 * L - 0.296 * S - 15.8 

    if cl_index >= 16:
        print("Grade 16+")
    elif cl_index < 1:
        print("Before Grade 1")
    else:
        print("Grade", round(cl_index)) 
    

if __name__ == "__main__":
    main()
