

class DSU {
    int* rodzic;
    int* ranga;

public:
    DSU(int n)
    {
        rodzic = new int[n];
        ranga = new int[n];

        for (int i = 0; i < n; i++) {
            rodzic[i] = -1;
            ranga[i] = 1;
        }
    }


    int find(int i)
    {
        if (rodzic[i] == -1)
            return i;

        return rodzic[i] = find(rodzic[i]);
    }

    // uk³adanie drzewa
    void unite(int x, int y)
    {
        int s1 = find(x);
        int s2 = find(y);

        if (s1 != s2) {
            if (ranga[s1] < ranga[s2]) {
                rodzic[s1] = s2;
            }
            else if (ranga[s1] > ranga[s2]) {
                rodzic[s2] = s1;
            }
            else {
                rodzic[s2] = s1;
                ranga[s1] += 1;
            }
        }
    }
};
