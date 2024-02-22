        }
        cout<<bit[i]<<endl;
    }
       cout <<query(n-1) << endl;
    while (q--)
    {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1)
        {
            if (l - 1 >= 1)
            {
                if(query(l-1)-query(l-2))
                update(l-1,-1);
                else update(l - 1, 1);