def checkio(data):
    output = ""

    if ( data // 1000 ) != 0:
        output += "M" * (data//1000)
        data = data % 1000

    if ( data // 900 ) != 0:
        output += "CM"
        data = data % 900

    if ( data // 500 ) != 0:
        output += "D"
        data = data % 500

    if ( data // 400 ) != 0:
        output += "CD"
        data = data % 400
    
    if ( data // 100 ) != 0:
        output += "C" * (data//100)
        data = data % 100

    if ( data // 90 ) != 0:
        output += "XC"
        data = data % 90

    if ( data // 50 ) != 0:
        output += "L"
        data = data % 50

    if ( data // 40 ) != 0:
        output += "XL"
        data = data % 40

    if ( data // 10 ) != 0:
        output += "X" * (data//10)
        data = data % 10

    if ( data // 9 ) != 0:
        output += "IX"
        data = data % 9

    if ( data // 5 ) != 0:
        output += "V"
        data = data % 5

    if ( data // 4 ) != 0:
        output += "IV"
        data = data % 4

    if data > 0:
        output += "I" * data

    #replace this for solution
    return output

if __name__ == '__main__':
    #These "asserts" using only for self-checking and not necessary for auto-testing
    assert checkio(6) == 'VI', '6'
    assert checkio(76) == 'LXXVI', '76'
    assert checkio(499) == 'CDXCIX', '499'
    assert checkio(3888) == 'MMMDCCCLXXXVIII', '3888'
