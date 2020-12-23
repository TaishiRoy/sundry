# open-webpage.py

import urllib.request, urllib.error, urllib.parse
import numpy as np
import T1
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

    T1.main()

    val = 1
    each = np.array(['xx', 'xx', 'xx', 'xx', 'xx'], dtype=object)
    blob = []

    print("\t---Extracting COMPLETED---")

    for eachurl in range(0,17):
        #response = urllib.request.urlopen(eachurl)
        #webContent = response.read()
        f = open((str(val) + ".html"), 'r')
        val+=1
        #f.write(webContent)
        webContent = f.read()
        f.close()
        tokens = [ 
            'NAME_PRE',
            'NAME',
            'NAME_POST',
            'TITLE_PRE',
            'TITLE_POST',
            'TYPE_PRE',
            'TYPE_POST',
            'VENUE_PRE',
            'VENUE_POST',
            'YEAR_PRE'

                ]

        def t_NAME_PRE(t) :
            r'<title>dblp:'
            return t

        def t_NAME(t):
            r'[A-Za-z0-9\s.\,\?/()\+:-]+'
            return t

        def t_NAME_POST(t) :
            r'</title>'
            return t


        def t_TITLE_PRE(t) :
            r'<span\sclass="title"\sitemprop="name">'
            return t

        def t_VENUE_POST(t) :
            r'</span></span>'
            #r'.html'
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

        def t_VENUE_PRE(t) :
            r'<span\sitemprop="name">'
            #r'dblp.org/db/'
            return t

        

        def t_YEAR_PRE(t) :
            #r'<li\sclass="year">'
            r'<span\sitemprop="datePublished">'
            return t


        

        def t_error(t):
            t.lexer.skip(1)


        lexer = lex.lex()

        
        attr_name = 0
        attr_title = 0
        attr_type = 0
        attr_venue = 0
        attr_year = 0

        def p_name(p):
            's : NAME_PRE NAME NAME_POST' 
            #print("NAME of PROF: ", p[2])
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
            each[3] = attr_venue

        def p_year(p):
            's : YEAR_PRE NAME TITLE_POST' 
            #print("YEAR: ",p[2])
            attr_year = str(p[2])
            each[4] = attr_year
            blob.append(np.copy(each))


        def p_error(p):
            pass

        parser = yacc.yacc()
        parser.parse(str(webContent))

    print("\t---Parsing COMPLETED---")


    inp_name = input("Enter name of professor: ")
    inp_title = input("Enter title: ") 
    inp_type = input("Enter publication type: ") 
    inp_venue = input("Enter venue: ") 
    inp_year = input("Enter year of publication: ") 
    #print(blob)
    for el in blob:
        #print(el[1])
        if (el[0].lstrip()).lower() == inp_name.lower() or len(inp_name) == 0 :
            if el[1].lower() == inp_title.lower() or len(inp_title) == 0 :
                if el[2][0].lower() == inp_type.lower() or len(inp_type) == 0 :
                    if el[3].lower() == inp_venue.lower() or len(inp_venue) == 0 :
                        if el[4].lower() == inp_year.lower() or len(inp_year) == 0 :
                            print('<', el[0], '>   <', el[1], '>   <', el[2], '>   <', el[3], '>   <', el[4], '>')







if __name__ == "__main__":
    main()
