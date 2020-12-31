import urllib.request, urllib.error, urllib.parse
import ply.lex as lex
import ply.yacc as yacc
import pickle

def main():
    url = "http://csrankings.org"
    response = urllib.request.urlopen(url)
    webContent = response.read()
    f = open('csrankings.html', 'wb')
    f.write(webContent)
    f.close()

    print("List of Venues according to subject area:::::::::::::::\n\n")

    venueList = []

    tokens = [
                'SUBJECT_PRE',
                'SUBJECT_OR_VENUE',
                'SUBJECT_POST',
                'VENUE_PRE',
                'VENUE_POST'
            ]

    

    def t_SUBJECT_PRE(t) :
        r'</span>'
        #print(t)
        return t
    
    def t_SUBJECT_POST(t) :
        r'<div\sclass="table-responsive"'
        #print(t)
        return t
    
    def t_VENUE_PRE(t) :
        r'dblp.org/db/conf/[a-zA-Z./]+">'
        return t

    def t_VENUE_POST(t) :
        r'</a>'
        return t

    def t_SUBJECT_OR_VENUE(t) :
        r'[A-Za-z\s\\.^&;-]+'
        #print(t)
        return t


    

    
    
    def t_error(t):
        t.lexer.skip(1)

    lexer = lex.lex()

    def p_subject(p) :
        's : SUBJECT_PRE SUBJECT_OR_VENUE SUBJECT_POST'
        #'s : SUBJECT_OR_VENUE'
        print(p[2])

    def p_venue(p) :
        's : VENUE_PRE SUBJECT_OR_VENUE VENUE_POST'
        #'s : SUBJECT_OR_VENUE'
        print(p[2])
        venueList.append(str(p[2]))


    def p_error(p):
            pass

    parser = yacc.yacc()
    parser.parse(str(webContent))

    with open("venues.txt", "wb") as fp:   #Pickling
        pickle.dump(venueList, fp)
        



if __name__ == "__main__":
    main()