# open-webpage.py

import urllib.request, urllib.error, urllib.parse
import numpy as np
import pickle
import ply.lex as lex
import ply.yacc as yacc


def main():
    '''url = ["https://dblp.org/pers/hd/g/Ganguly:Niloy", 
            "https://dblp.org/pers/hd/m/Mukherjee_0001:Animesh", 
            "https://dblp.org/pers/hd/g/Ghosh_0001:Saptarshi",
            "https://dblp.org/pers/hd/m/Mitra:Bivas",
            "https://dblp.org/pers/hd/c/Chakraborty:Sandip",
            "https://dblp.org/pers/hd/t/Talukdar:Partha_P=",
            "https://dblp.org/pers/hd/n/Narahari:Y=",
            "https://dblp.org/pers/hd/b/Barman:Siddharth",
            "https://dblp.org/pers/hd/g/Goyal:Pawan",
            "https://dblp.org/pers/hd/d/De:Abir",
            "https://dblp.org/pers/hd/s/Singla:Parag",
            "https://dblp.org/pers/hd/k/Kumar_0001:Amit",
            "https://dblp.org/pers/hd/c/Chakrabarti:Soumen",
            "https://dblp.org/pers/hd/s/Sarawagi:Sunita",
            "https://dblp.org/pers/hd/d/Dasgupta_0001:Anirban",
            "https://dblp.org/pers/hd/r/Ravindran:Balaraman",
            "https://dblp.org/pers/hd/d/Dey:Palash" ]'''

    print("\t---Extracting HTML---")
    f = open('professor.txt', 'r')
    url = f.readlines()

    f.close()

    val = 0
    each = np.array(['xx', 'xx', 'xx', 'xx', 'xx', 'xx', 'xx', 'xx'], dtype=object)
    blob = []

    for eachurl in url:
        response = urllib.request.urlopen(eachurl)
        webContent = response.read()
        f = open((str(val) + ".html"), 'wb')
        val+=1
        f.write(webContent)
        f.close()
        tokens = [ 
            'NAME_PRE',
            'NAME',
            'NAME_POST',
            'TITLE_PRE',
            'TITLE',
            'TITLE_POST',
            'TYPE_PRE',
            'TYPE',
            'TYPE_POST',
            'VENUE_PRE',
            'VENUE',
            'VENUE_POST',
            'YEAR_PRE',
            'YEAR_POST',
            'PAGE_PRE',
            'PAGE_BEGIN_OR_END',
            'PAGE_MID',
            'VOLUME_PRE',
            'VOLUME',
            'VOLUME_POST',
            'ISSUE_PRE'
                ]

        def t_VENUE_PRE(t) :
            #r'<span\sitemprop="name">'
            #r'dblp.org/db/'
            r'<span\sitemprop="isPartOf"\sitemscope\sitemtype="http://schema.org/BookSeries"><span\sitemprop="name">'
            #r'dblp.org/db/conf/'
            #print(t)
            return t

        def t_PAGE_PRE(t) :
            r':\s<span\sitemprop="pagination">'
            #print(t)
            return t

        

        def t_VOLUME_PRE(t) :
            r'<span\sitemprop="volumeNumber">'
            #print(t)
            return t

        def t_ISSUE_PRE(t) :
            r'<span\sitemprop="issueNumber">'
            #print(t)
            return t

        
        

        def t_PAGE_MID(t) :
            r'[-]'
            #print(t)
            return t

        
        
        def t_PAGE_BEGIN_OR_END(t) :
            r'[0-9]+'
            #print(t)
            return t


        def t_NAME_PRE(t) :
            r'<title>dblp:'
            return t

        '''def t_VENUE_POST(t) :
            r'/'
            #r'.html'
            print(t)
            return t'''


        '''def t_VENUE(t) :
            r'[A-Za-z\s\\.^&;-]+'
            print(t)
            return t'''

        def t_NAME(t):
            r'[A-Za-z0-9\s.\,\?/()\+:-]+'
            return t

        def t_NAME_POST(t) :
            r'</title>'
            return t

        



        def t_TITLE_PRE(t) :
            r'<span\sclass="title"\sitemprop="name">'
            return t

        

        def t_TITLE(t):
            r'[A-Za-z0-9\s\t]+'
            return t

        def t_VENUE_POST(t) :
            r'</span></span>'
            #print(t)
            return t
        

        def t_TITLE_POST(t) :
            r'</span>'
            return t


        def t_TYPE_PRE(t) :
            r'<div\sclass="nr"\sid="'
            return t

        def t_TYPE_POST(t) :
            r'">'
            return t

        

        def t_YEAR_PRE(t) :
            #r'<li\sclass="year">'
            r'<span\sitemprop="datePublished">'
            #print(t)
            return t

        

        

        

        def t_error(t):
            t.lexer.skip(1)


        lexer = lex.lex()

        
        attr_name = 0
        attr_title = 0
        attr_type = 0
        attr_venue = 0
        attr_year = 0
        attr_page = 0
        attr_volume = 0
        attr_issue = 0

        def p_name(p):
            's : NAME_PRE NAME NAME_POST' 
            print("Scanning for ", p[2], "...")
            attr_name =  str(p[2])
            each[0] = attr_name

        def p_title(p):
            's : TITLE_PRE NAME TITLE_POST' 
            #print("TITLE: ",p[2])
            attr_title = str(p[2])
            each[1] = attr_title

        def p_type(p):
            's : TYPE_PRE NAME TYPE_POST' 
            #print("TYPE: ",p[2])
            attr_type =  str(p[2])
            each[2] = attr_type

        def p_venue(p):
            's : VENUE_PRE NAME VENUE_POST' 
            #print("VENUE: ",p[2])
            attr_venue = str(p[2])
            #print(attr_venue)
            each[3] = attr_venue

        def p_year(p):
            's : YEAR_PRE PAGE_BEGIN_OR_END TITLE_POST' 
            #print("YEAR: ",p[2])
            attr_year = str(p[2])
            each[4] = attr_year
            blob.append(np.copy(each))
            each[6] = 'xx'
            each[7] = 'xx'

        def p_page(p) :
            's : PAGE_PRE PAGE_BEGIN_OR_END PAGE_MID PAGE_BEGIN_OR_END TITLE_POST'
            attr_page = int(p[4]) - int(p[2]) + 1
            each[5] = str(attr_page)
            #print(each)

        def p_volume(p) :
            's : VOLUME_PRE PAGE_BEGIN_OR_END VENUE_POST'
            attr_volume = int(p[2])
            each[6] = str(attr_volume)

        def p_issue(p) :
            's : ISSUE_PRE PAGE_BEGIN_OR_END VENUE_POST'
            attr_issue = int(p[2])
            each[7] = str(attr_issue)
            #print(each)


        def p_error(p):
            pass

        parser = yacc.yacc()
        parser.parse(str(webContent))


    inp_name = input("Enter name of professor: ")
    inp_title = input("Enter title: ") 
    inp_type = input("Enter publication type: ") 
    inp_venue = input("Enter venue: ") 
    inp_year = input("Enter year of publication: ") 
    inp_page = input("Enter page count: ")
    inp_volume = input("Enter volume: ")
    inp_issue = input("Enter issue number: ")
    #f = open('blob.txt','wb')
    
    '''with open('blob.txt', 'w') as filehandle:
        filehandle.writelines("%s\n" % place for place in blob)'''

    with open("blob.txt", "wb") as fp:   #Pickling
        pickle.dump(blob, fp)


    #print(blob)
    for el in blob:
        #print(el)
        if (el[0].lstrip()).lower() == inp_name.lower() or len(inp_name) == 0 :
            if el[1].lower() == inp_title.lower() or len(inp_title) == 0 :
                if el[2][0].lower() == inp_type.lower() or len(inp_type) == 0 :
                    if el[3].lower() == inp_venue.lower() or len(inp_venue) == 0 :
                        if el[4].lower() == inp_year.lower() or len(inp_year) == 0 :
                            if el[5] == inp_page or len(str(inp_page)) == 0 :
                                if el[6] == inp_volume or len(str(inp_volume)) == 0 :
                                    if el[7] == inp_issue or len(str(inp_issue)) == 0 :
                                        print('<', el[0], '>   <', el[1], '>   <', el[2], '>   <', el[3], '>   <', el[4], '>   <', el[5], '>')
                                        if el[6] != 'xx' :
                                            print('< volume :', el[6], '>')
                                        if el[7] != 'xx' :
                                            print('< issue :', el[7], '>')

    return blob








if __name__ == "__main__":
    main()
