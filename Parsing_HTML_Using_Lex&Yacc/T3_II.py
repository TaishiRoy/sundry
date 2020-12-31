import pickle



def main() :
    with open("blob.txt", "rb") as fp:   # Unpickling
       profInfo = pickle.load(fp)

    unfiltered = []

    print(profInfo[2][1])

    with open("venues.txt", "rb") as fp2:   # Unpickling
       venue = pickle.load(fp2)


    inp_name = input("Enter name of professor: ")


    print("\n\n\n\nPapers which has been published in the selected venues that are obtained from crawling from csrankings.org ::::::::::::::\n\n\n")

    for eachProf in profInfo :
        if (inp_name.lstrip()).lower() == (eachProf[0].lstrip()).lower() :
            for eachVenue in venue :
                if eachProf[3] == eachVenue :
                    print(eachProf)
                    unfiltered.append(eachProf)


    print("\n\n\n\nFiltering by papers which are at least 6 pages long ::::::::::::::\n\n\n")

    count = 1
    for el in unfiltered :
        if int(el[5]) >= 6 :
            print(el)
            count+= 1

    print("\n\n\n\nThe number of top conferences full paper the professor has -------------->  ", count)


if __name__ == "__main__":
    main()