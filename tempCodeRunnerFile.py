 for i in range(l):
        if sett[i] ^ i > k or sett[i] == i:
            return False
        if sett[i] <= i:
            insert_ind = i