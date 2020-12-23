import urllib.request, urllib.error, urllib.parse

def main() :
    print("\t---Extracting HTML---")
    f = open('professor.txt', 'r')
    url = f.readlines()

    f.close()

    fileNum = 0

    for eachurl in url :
        fileNum+=1
        response = urllib.request.urlopen(eachurl)
        webContent = response.read()
        f = open(str(fileNum) + '.html', 'wb')
        f.write(webContent)
        f.close()


if __name__ == "__main__":
    main()