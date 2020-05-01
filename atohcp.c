/* Library.ascのカードをHCPに変換 */
int atohcp(int a)
{
    switch (a) {
    case 'A':
        return 4;
    case 'K':
        return 3;
    case 'Q':
        return 2;
    case 'J':
        return 1;
    default:
        return 0;
    }
}
