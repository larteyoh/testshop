#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace neroshop {

struct Category {
    unsigned int id;
    std::string name;
    std::string description; // or alt. names
    std::string thumbnail;
};

struct Subcategory : public Category {
    unsigned int category_id;
};

//-----------------------------------------------------------------------------

const std::vector<Category> predefined_categories = {
    { 0, "Miscellaneous", "Others;Non-classified", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAACXBIWXMAAAsTAAALEwEAmpwYAAACbUlEQVR4nO2aT4oTQRSHS5mlbkTRCyg4oxdQZ+sJTFzPKUTcCK7nAEJWji4mzBHcZDMqguNC8ABKZlZDsjIb88ljSgjdVd1J6k+69H3QkG5eNfX7db1X1Z0yRlEURVGUTQBcMqUA3APeAWd0l1Pbx53Y4p8CM8pB+tqLJf5+YeL/MosyErgYUqVyEMOAM8rlNIYB80yd/SB5G3DsO+45j2FALoaB/RQTaqgBoZAPHQEm7EFpCqA1oI7WgFDIh9YAE/agtAagNaCO1oBQyIfWABP2oLQGUHgN+CFpEHAcl25AEtSAUCgcNSAU3Bw3FKOvwAR43xAjBa+tCI5aHu5ok0Ww54l9tfAV+RzY9cRJh73rAOAW8L1B/Ovq/4q51wE9R9wdxyf0L6sasI74rhjw2BE3WcWAdcV3xYBrdtgvcriCAaN1xdt79jdqgCA5L8PeFsFD4LpZ3gACxHtHjkllAPACGNvjeUP7G8ARMAVOrEnDHOJTGnDkuNb3tK/GntspMrn4lAZMHdcGnvau2EkO8SkNOHFcc6aBI3buaR9dfEoD9oBPC+cfgSue9rsLs4OIf9lSA6KJT10Et4CHwAP5bWOv2uI4kH1FlSlS1gm37fkwh/ikBph6nBjyecm08K0DQsTnnQZNPe6RI268ggHeb4LATeBbg/jBxhdCXKRDlZ+hBiwp/nIXlsJblcIoPAsxYJV3g5QGzB333fdsVNqzU9zUivRtaJINUW2bpPpL5Hy/ZZPU7/99m9w4hgFvKZc3MQzYKXSr7C9gO9gAwebarDDxT0xMgG2bDvL621WkbwfA3ajiFUVRFEUx/yJ/AKs6hY9h/vEkAAAAAElFTkSuQmCC"},
    { 1, "Food & Beverages", "Grocery", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAACXBIWXMAAAsTAAALEwEAmpwYAAACZUlEQVR4nO2aPWgUQRSABy0iokRIdWoTBJtoIVqEgD+NINHCZiWFprCykYDa2MUmimBjCrWyCAouBCwEC7GwUUyTwlILrSL4V0RBRf3CoMKRm73d2503vovvg+lm3sz72Jmdt3fOGYZhGIZhdAEYR47limvIQoML+uaBrnmVeYIAJ5FlQLuAKWEBLe0CpoUFjGgXMCssYL92AXeEBRzXLuChsIDT2gU8FxZwQbuAV8ICZrQL+Cgs4KZaAcB64KewgFyzgCHkeaxZwE75/FnULGBUPn/eaBYwLp8/nzULOEUaBrQKmCINLa0CLpGGEa0CrpOGjooQGP6TuG/XCsZlgfYs0O+e1kqwsCIEJojHrNZKsLAiBA4Tj4t1BSyQho6KENgbMf5YXQEvScNMwRkQg7fAuroCPpCGW4G5t0SKfb5W8h5/SyMNt90qgM0R4voneIOrC/CJNHR8EwAGG8ZcBnbXTt4DvCYNV90qgG0N4r0HDrqmAPOk4URg7kM1Yz0BdjRO3gOcQ55fwHYXvgj9qBjjC3AfOOZiArSAb8ICHnWZ358DY8CVgrFHgF3AxqiJtwPMCQs46kropRiKDrBV8Mvwg4pr+HcCPMCkQPLvvFzXDwI8/kYVMXl/v9jnKqJCgAc4C3xtmLz/pWmP6wE1Ajz+dlXw0aGM78ANYJPrEVUC/gIcAO4CSyXv+BfA5dC7vq8FtAOcKRAw5CLQDwIyyQWaAOwJyGwLCG6xxtgZgB2C2Zo+BPn9P4G8S3saWmDJmLyfBGQI0HR+2azbMAHYE5D971tgtOxAq9Oazi+btWEYhlvbrADFelwIpcui8wAAAABJRU5ErkJggg=="},
    { 2, "Electronics", "", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QA/wD/AP+gvaeTAAACO0lEQVR4nO2bTU7DMBCF3yDgFGVBWSNY0ntQDsJBABXBHWgP0u6Q+FkCC3qKIvpYpEShHbeJk9gpmW8VWZN4ZuJxZmwHMNqNVPUgkh0AvZUOREaKbA9AZ6l5KiJjRbavdDcWkamvrrVAsk8Fh+xQER06ZDU0p3ixU9WDthVzQGwFYtN6BxiGYbSa0qkwyRMAfQCHAPZKa5SPLwAfAB5E5DlQn38huUvyjuTcka6GYE7yluRuDAfcRTR8mYGvHV4hwGTYP/reXwNzAKc+4eCbCZ6jOcYDiR3nPjemscMC9TyArk9nNXOkNXLDekJ28ugB0Gpy7U2Hmu2LsO9o12y6ADACrBgyB5gDYisQm3QSXMz2Tfq0VYKIrLXJRkDAvqYAVtb9HWj7BrUQ0gFjEbnII8hkj6Cytf91WAj8XpA8A3C5LJD3rTUV6jtOVyIyAf6GwAECDbvAaDaNAEwACwFzQOsdkJ0DPrEoEf8Zmk2fvxfZVHiCpE7+V2z6ilkIBOyr5/gmq7K1apIhpAM6aGCe0foQSB3AAoectgnHRko6Em0ExFYgNuaA2ArEJvsZHCN/JvhVgy5lmTnaNZvSpblsKjxF/lrgPb9ewXjTGh17mym+ITBCsiXdFObwLOS8HCAiTwDufe6tiVsReQnaI5MjMgOS31Uf9yjAN8kbljgiU8UhqWMkOX4X7i3qqpkhmYceROQ1UJ+GYRiGE9pPU9uJOSC2ArFpvQOqXBYvsp5wjdXqzfUr7Np63jDK8QNj5L+yJWBCUgAAAABJRU5ErkJggg=="},
    { 3, "Home, Furniture & Appliances", "Domestic Goods;Furniture;Home Appliances", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAACXBIWXMAAAsTAAALEwEAmpwYAAACoUlEQVR4nO2Yy2oUQRSGKwkqibeFF0SjuPC+EQQvuPJGEEEGldmKlxAUl6KQjQhufAEvoIIuTGBwo75BXAgRdRtcqJgH0BiiRoVPjvSQoadrpipOV1W39UHv6tR/6lD9V9VRKhKJRCKRSCQSmRdAH7APqABVR18l0exVvgC2AqPADP4Q7RFgi+vFDwKzhIPkct7V4s8SLkMutv0s4SK5bc6zAKOEz+M83X6G8JEc+/IowF6Kw548ClChOFTyKECV4lCNBeg0xB3ACf5zD+gGrgI/CZdvwAWgq+MFqAOcDLQIcv4fUS4AhgiPU51YWC9wEDgKbGgz9inh8LBNrpuAY8B+YHHWgEXATWAqNfEYsEMz6TbgN/6R33Fji9vry9T4L8ANYGGjuT1vIfAZ2KkRqOGfEU1uh9u8XWQHd8vAMwYiE8CCDJFD+OeA5lf+aBB7Wga/MBQ6lyHUBbzDHxNZR15yFJowJoOnDQe/0my1K/jjsianN4bxUzL4u4XgrgyxVcAP3COaKzPy2W0xx7QEvLUIuBtQp0hnfvcs5hiXgGsWAV+BJZrjpub4a2p6AMssfmlhWIL6Lc/zQRUowEWLdfwC1tYDn1kEjqtAAV5brONJY+Bx7GgyQ99Ymp8w0BjcY3hxqHNbBYal+b3/ewtsBLhuaYZLVSCIMSc5mTKcNUl/II+bvJkzvzRtHkVlYc780szDDIvIQKsC9FiaYdFoNr80lmZYNJrNT2OGITY9O/F4WqNMAO5TPm4ZLV4AVgCfKNe/v1zZAGwvSRE+SFfYavF1gNXAo4JekOTC8yCraWINsB64JA2R5C0+mSE46bAX0Er/TvIsXvfPC9ehaYfXlCN86yvfCfjWV74T8K2vfCfgW1/5TsC3fiQSiUQiEVUK/gB5u4ODDC6IPAAAAABJRU5ErkJggg=="},
    { 4, "Patio & Garden", "", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QA/wD/AP+gvaeTAAAD20lEQVR4nO2aT6gVVRzHv7+UMk3RAjErynTRoiBCqAdtcmEiUiFkqxbRrnbiQiLquVKTstxIGOTGzQvJlegiwUUlRJYP+iMYQaWP0pSnkvi093Ex8+h6PWfuPTPnzNyb84EL78098/v9vt8798y5vzNSS0tLS0tLy+2KNV1AJ8AcSaslPSfpKUmPSrpX0lxJFyVNSBqXdEzSUTP7tqFS4wIsB3YDk4TxPfAGcHfTGkoBLAB2AtcChXfzK7C+aT1BACuBXyoK72YMmNe0tp4ALwH/RBY/w3HgwX5rqX0SBF6UtF/SrIJhVyV9Iem4pL8knZW0UNmkOJK/is4/KelZMzsXo+ZokF32RZ/8b8BrwPwecRYD7wDnC2J9zSBNjsB84JSn2GlgKzA3MOYS4ECBCe+n0hMMsMNT5BTwaoW4BmzzxL4OPB1TR9kiH86FunglUo6PPPG/jBG/anG7PMXtjphjNvCVJ88zsfKUKewu3JPVBJEnKeBJ4F9Hrn0x84QWtdbzqbyVKN/njlzngaLbZjqA9xwFTQGLEuV7wWP4Stf4O1IU0YUr8biZXUiU74ik647jzrtBHQYscxw7liqZmV2W9LPjraWu8XUY8Ijj2Juey7QMZ4DNXfH/cORc4iouyADgceAg8BPwIXBPyPmJuF/SVuDljmNTjnGzXSc7D7ogu5celrQgP/RY/lrTb4zErJX0Wf6367fERddJfV0BwIhuFj8TcEtAganp7AOscLzvnHR7XgG5+EO6VfzzZpZsMisLsEzSQ463TrjGFxrgES9JYwHiN/Q5riozE58v3zdB0YAHKP69PVqp3AQAd5L1B7tx3RZ7Btvcxy1ooEwANnnqDF92dxkwCawHLoea0IeJsTiBu9t0lYAeYWfhS8m+ApNkc4GAdz3JvSYkkRrGB8HiO4ofIRef/z8POO1J5DShNpluzgH3lTbAI+j1goTbBsiAabIOdFyAWcB4QeLRrvFNccuHEdOEVf0mr0Opg4+BtHsewKEeRYw2YMBMez39hg/wBFnbuYjR5JL/429gXXLhXSbsqVFgL8bKaKjaEHlb0qWKMRqlkgFm9qek8guNASBGS2y7pN8jxGmEygaY2RUNVmMkiFhN0U8lfRcpVq1EMcDMpiVtihGrbqK1xc3siLK+4VARe19go9y7MgNLVAPM7EdJe2PGTE2KnaGhWhxFN2DYFkep9ga3y70/N3AkMSBfHA1Ux9hHyt3hoVgcJTNgWBZHSZ8PyBdHEylzdHC6zEl1PCCxq4YcVyR9UubEWh6WBjYoe44gxQMVZyTtMbMfEsRuaWlp+X9zA8EbEeUfOYl4AAAAAElFTkSuQmCC"},
    { 5, "Digital Goods", "", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAACXBIWXMAAAsTAAALEwEAmpwYAAADS0lEQVR4nO2au2sUURSHJ7Exia9SRURJRA2oENFNQLcUFXQ3ypYSNBZaqcFCUCSinfgfmMZkjaQSQTvFJ9qorYiFj8JnhEACRtFPDrmRzc25szNj2Mks94Ot5t7fnPkx9+ycc28QeDwej8fj8VQBKKEQMr4BKAIjwHtgEvgEPAT6gMUhc2WOzYhjrEYpSNMAYC3wjHC+AN11ZwCw0TxcFP4Ax+vGAKAFeEM8fgH5ejHgHMl4ITkj0wYwlfQ+OF7zIeAIcBEYcwTdmXUD2h3B9Fs6HcBPZdz5rBuwxxHMckXrsTJuIOsGlMKuW1qhD+gNwL8BI34JzMbngGCeJ8GCI5gWReuOMm4o60kw5whmRsEDLANGlXGXs25AEzCuDJESuBtYAmwB7juCPpBpAwTzyZuEb5VLJcsGtAE/EhhwwtLJpgECcCjmw98EGoN6MUAAeiK+CdeAhYFF5g0QgFZgUEmMv4EnwN7AwXw1YJUxYcYvwjz5d9gO7Ad2atWhMqdLuVeXY+ysmCTWpM/p8Xg8sTBJrtMUQ3lgxX9orTQaBVNbNEWYk04SBNYBZWBC6QI/BfbF0CqYnSSZW8mE+SttC5lbm7/BSoDDZq+vGmXtQ8d6e4Yj6MhHVc+8MICpr7w4SO2/QNFpBG7F1DqaqgFMvfZJip1TitbpBDpy79Y0DSiTjFGr3F0EfE+oNZiKAUCzkvCmGx5F0/DYDNxzBHWwWl0B3AU2Ga2i0bYZr/x3qKUBOcfNita4pabBEdbyuqJc/ypzLS3pJGlsS8OAwhw2PbWldFvRke12jUIaBpS0O6W99eUN0PFvQOCXwByDzwHsjnEAQnp+Nlcrrg8o1x85qkONXWnkgHbHzS5Y47aak19hR2D6letybKbD0pIzRRob0jCgwZz41LgO9AKXQg5B5aymp8aY0egNqRLfWifKamOAAJwlGc+toKUSfJlQ68y0ThoGNAOvYwYsy2GHopV3LJUwXtldopoaIMj6Az5HDFg2QY4FDuSYrNIFciGF0XpFo7YGCMAaR6a3A/73ze7CFDzVDJVjdasd82tvQEVSlN2eG8A70yL7aPb/T0rNH0REjs5L0wR4YIybNMluuFpvMTUDPB6Px+PxBFnnL5kjkrLcntRPAAAAAElFTkSuQmCC"},
    { 6, "Services", "Non-product services, Freelancing, etc.", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QA/wD/AP+gvaeTAAADjUlEQVR4nO2aS6hNURjH/+t61c2juCjKsy5loCiuiTKiFGUiTEQxo0gGCteEiYmZPGbUjQkhRhQDEiZInYG8out6XFeKe/kZ7H1qO/fsx7l7rb3Ocfdvck77nG+t7/+tb639rbW3VFJSUjKKMb4dkCRgk6T1kiqSThljfnh2qTiALfzLZd8+FQpwrSYAQ8Ak3345B5gHHAR6Gc5pYLVvH50ATAPOA4N1hNfyAOjy7XMugA6gM/y+AnifQXiUQeBAaD8DWOhXUQMAe4CfoZDnwECD4qM8BP6E368DE3zrS4Qg1X/lEJzGDht+ttloJIapksY5bH+GjUacBcAYU5F0N+PfK5KuSHog6XeG/w9Iav56AZgC3ElI4wFgZ41NJ/AkwaYfWO5LU8MANxudx8Bs4HOMzRAwpWgdIwZ4FyOkkmJ3PCFwq2z553IRrNIRc/15it2zhN+mj9CXYRQRgO8x19NEzEz4bWCEvhQPQQETN5c7Y2zagEcJU2CuLf+KyIC4VB8jqQeYE70ItEk6KWlZjN0XSR/suecQoDthFKt8DRe8bcD+lJGvch+Y6FtfIsDMMM1dsduGny6nQLuCNHfFZBuNuCyFX0q6HrlEziaj9p8k9eRsT5LjQ1GCLetWBbe0G5I2Sjo2gqbuStouaZ2kSZIuGmPe2PKzUIANZD8UGQROAON9+20VoB3Yy7+HHFHeAqeABb59dQ71d4vWSt00iiiE0qg9M3hhjPnoxRMfhNPhAsE+/yGw1LdPLQ2wBLgC9AGvgLNA3I70/wLoIiita3kKtNezsV4HhPf+TkmzZKFaM8Zcythvl6RbCX3uMsacyetPkgNrgMvkO/sfRsa+u8I1JInT9WzHWhA+S9I5BVVa4WQY+Sp9LjpfTlC0uOJnSv+rMow8BMXWStvis6RdXmLPDckuHuBQK4oH6LYg/miriq8Aw+Y1nsU30nkeHgHzixCfuQ4geBhxU/nv7b2S7qn+M8D3km5LumqM+ZOj/25jjL3RbzDyaSxy3H/Tp/3iZhKfOAWwl/ZRPirYAmd5DC5JazP239Rp75oj1oSPNvFxJ0K/lD1FfXLUGFO3WMoNQZ0f95JCM2A37VssCO7FR4LQbOvB4cLEN1kQXgObbWtzUQp/k7Qv/LTBkKQ3kh7XlseFQ/qa0E+rv9ycRkIQ/n/xVeoEYfSIrxIJwugTX4Xg7mDtpcWSkpKSkoL5C2IZ98cgmOE6AAAAAElFTkSuQmCC"},
    { 7, "Books", "", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QA/wD/AP+gvaeTAAACCklEQVR4nO2bPWsUURhGz00iWlgYFAtbQRFUgiCI2NjZJgEbSZlOsNTKP2EnNmkCaZLCzkL8HYpg4QeSEAJiEVEeC7dY1M3c3XnnPpPde6plZ/flzNll7sDehcpskyZ5k6Ql4CpwHjgRahTPTkrp7aiDC7lTJCVgDXgKXAwQK8U7oF0ASaeADeB+kFRvmMt83Qum8OQhI4CkZeBBARcLOd+AJ51bGDkygKQLwM1CLhaavgGXmHCpPC40BVgsYmGkKcBUf/owxo1QBu+Bg8B5TSwA18hfykcOieAbcDml9CtoXhaStoHlNjNa1RvisPTJD/jedkBUgGNLDeAWcFMDBM1x3S+09o9aBs9Keg7sB83LYR6413ZI5I3QeuCsYtRrgFvATQ3gFnBTA7gF3NQAbgE3NYBbwE0N4BZwUwO4BdzUAG4BNzWAW8BNDeAWcFMDuAXc1ABuATc1gFvAzcwHaPPb4E/+7A3qOz8mfqekFf3LlqTbkuYDJfvJfwI8dDsV5a8AL90+XTDORXCzMwsjTQEOhx7vdSnioinAx6HH17sU6SWS5iR9HlwDPkg67XYqjqTHQxfCV5LOuJ0iadzeJukk8Aa4NXjqC/AMeA3sdqcWxteU0sg9xVn7+ySdA3aAO1FWBVlNKW2POpi1DKaU9oC7wCPgU5BYLxh7h+fgH6Q3gCtMwV9nK7POb7zRpspIHJDQAAAAAElFTkSuQmCC"},
    { 8, "Movies & TV Shows", "", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QA/wD/AP+gvaeTAAAC7ElEQVR4nO2az2+MQRjHv09pohHclBIkUhc/Dhqk6iYSN0LqVxxxpPEPkHB0QURE4w/g5CROIkSJgyoJ4kaiKRJpKyG0/Ti8u0mzZrbv7nR3urvzOT7vPLPf7zM7M/vujJRINAyAAT2xdUShYP4GMAUci62nrswyX2QKOB5bVy6AbuBSQL4Bt/ifP8Ch+dQ67wAngYmC4DNV5PvMFxkBFtdCexBAB3C1ROwvYFsFfZR+7Ut5D3TV0kfVAIMe0W+Ajhz5c438O2BVPbxUBdAJjHrE35wjt3FHfjbAfmDGY8K5jTWN+SLAFY+RH8CGkrbNZV6SgHZgyGPoBdBeaNd85osAG4Fxj7HLTW2+CHDCY24aeFDG/MJe7SsBuFPGaLSRt5ziV0g6LemgpG5JK2spKoAxSR8l3Zd028zGg3sEjgLfKxy9hcA3oD/U/Dn8e3kjMAOcLefROwWAvZIeSloUVMX4TEvaZ2aPXA+dBQDaJA1L2lpDYfXktaTtZjZT+sBXgD2SnjgeTUq6JumtssrWg9XKFuAtgf30mdmzXC2Bi4759BfYESiiKoAlZG+SIVxw9d3m+cz1jthzM3s5f7byY2a/JQ0GdrPOFfQVYKkjNhooIJQvrqA5kHTP0XSZK99XgJYhFSC2gNi0fAEW3l/KFQLcdYR78+Y3fAEkBb3wtPwUSAWILSA2zbAGuH719Upamye54QtgZkdKY4WdIdfi2PJTIBUgtoDYtHwBGn4RBAjJb/lvQCpAbAGxSQWILSA2qQCxBcTGV4BJRyz2NZU1gfkTrqCvAJ8dsV3AzkARVUF2ufJUYDefXEHf4WifpKeORz8lXZc0ovodjnYpOxzdHNjPbjMbKg2WOx5/JSn33d4FzrCkHtfxuHMKFBoOqH6jXEumJQ24zEtldoHCjYrzkoJeNiKDMvOPq+8B+skuHDUaX4HDc/nLe01uubKF6ICkTZI6q65obRmT9EHZNblBM3NufYlEIpFIJBKS9A+F5c3zqqADtAAAAABJRU5ErkJggg=="},
    { 9, "Music & Vinyl", "Musical instruments", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QA/wD/AP+gvaeTAAAFHUlEQVR4nO2bXYhVVRTHfzuiJBuNMc2ERDJ0irEilF4sDaIPeopAjaCnihF6k0CUEqLGeQoVfEh7CsqH8CnNqBCCCgqJzI9yCMf8wjKFGY0+EH897Gtex3POPV/3XsH5w8DM3mevtf777LP2WmvvgQlMYAITuI4ROqVInQH0A/OB2UAvcCsgcB44AxwDhoG9IYQznbKtLVBvUJeqm9T9FsPFxpgN6hK1Yy+qMtRe9Q3114KkszCirlF7u80vFeoUdUgdq5H4eIypg+qUbvO9Aurz6sk2Eh+PE+qybvNG7VE/7CDx8diu3tYt8vPV4S6Sv4RD6txOk1+o/tZl4s04pT5Uhkvh7UVdBOwm7uHXEsaAx0II3xcZVGgC1HuAr4A7iozrIE4Di0MIw3kH3JD3QbUH2En3ye8EhlL6pgMfN2ytF+q2bn7kDexQb27YM6BeSHluW93kV3SMYjr+J99k10DG8/XECcYI70RHKKbjKvJN9q1PGXPCHBFjHh+wBphVdOJqRi8wdXxjY1IWpIyZBayupNWY2LQzti+CEbWvmbxxZWRhzBYJ1I0t5uBVoG6POgrsAg4AxxttdwEPAE9k6JsD7FIfbsjYDjzTQlcPsBJ4u7CVxnz+SI1v8LD6gnpThs6p6ir1aIacb2z95psxYpl6grGYURc2m0E8Qfdk9d0a9S8pMwGbalK+qrDyyzasrcmGDWWUFy1jJWFzWfJNdmypwY79afITvw1jAfNUWn9OjAB9IYR/K8hAnQz8RHSUpcUA05MKrWlxQD/VK8avVyUPEEL4E9hYVQxwf1JH2gTMr6hwFPioooxmvAecqyijL6kxbQLmVFT2aau3ry5QNzZ++rOeDSGMAp9VtGl2UmNaIFS16rovq1NdAHwHTGo0vaIuCiGkOivgB+C5CjZdFUpD+gqoGv2dbNH/MpfJ0/j9pYoyWyGRU+6CSEG0cqDmbCsisxTSJmCsotxW2eNW4O+mv/8iOros3FnJonj+eBXSfMBoRWUPZnWGEPYbi6uXlv3WEMKBFjITt7ECyM9JXVkx8hpTE51OGRhT36pp+UCS7LRP4OeKNvfQ2qkVwXKqO+ZDSY1pofA0Yom5iuM5BtzbiORKQ51END5xH88rBpgZQvh9fEfiCmjEzAcrKIQYu79TUQbAJqqRBziYRB6yt8EvKiqFGOCsLTtYXU2MGapidxnlSyo6nWZsMWZ1eXVPUrfWqH9pmQkIxnJSXuwwlqvScNRY7krdHYze/kXrvV1yRE1d6ZlOzrh838oxXzuJcfpU4Fuyk6lzxMRmL9FRBqK/6Aeeov4i7LoQwpulRpqvLH7FoYXaZ7GV0060LIvnmYTBDAWJJzbqDLM/h05hsBW/PMnQEOmZ2L4Qwj8J7aPA2Ryy24mTwPpaJKnLMmZ5YNyzeU5sOoEVtZBvIpZ2PH7BxiR47ZDPfTyeO9Q1XjrYA8xLeWSIeFDZ6riq3RgGFoYQctUQi16RuRv4GphZwrBO4A/gkRBC7mSuUEUohHCY+IarFkzagXPA00XIQ4mSWOMW1mKq1+jqxFngyRDCno5pVOcaLyl2G4fUNL/U9knoUT/oIvn31e7fVzTGCZ28R3RcXd5t3lfAeJlq0PZeqTmvrlNv6TbfVBgTqDXWmxD9or6m3l63vW37VxTjtZRHgWeBx4H7CugT+BH4HPgE+DKEcLEddnbyn6amES9CzSPm/9O4fOH6PHErO0qM5PaFEE53yrYJTGACE7hu8R+yRA2BiW4OUQAAAABJRU5ErkJggg=="},
    { 10, "Apparel", "Clothing, Shoes and Accessories; Jewelry and Watches; Fashion", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADwAAAA8CAYAAAA6/NlyAAAACXBIWXMAAAsTAAALEwEAmpwYAAABhklEQVR4nO3av0rDUBSA8dBF7DP4B1wERxF8kD6HQlEonZrRVxDBTaFdXH0NDQ5uuluJ0k30kwsJ1JDatMk9p17Pbyq0cO7HTW5LSRQZY4wx5s8BtoFj4BZ4BCb4M8lmuFlHwJZk6CZwDnyg5xMYATu+Yzued3JRbi0dX7F94IvV49bUbzo2XnIxD8D6AnPWgLslZ51px+YugFaFOS3gknpi7djcFdD+ZU4buKYZsXZs7gk4AfbcZZ5FutenwDPNirVjNVS7pwOJrRZNWLG58migS7i6ZcFjwjUuC04IV1IWfACkhCd1bbPu4/3ALu0UOJx3UleJHqCvVzu2YvQg+4yqbA292rFzogdT76uaWkevdmzhIEuy8B/fZSgr+Q3xCtzPPKDqWqVgEViwLNth31DmPbDIgoVF0lBmwb5hOyzL+44WCfdZcCQN22FZtsO+ocx7YJEFC4uk8Q+D3xV7U43gG8XgoUbwbvbXqLQXYEM8eOqpPPdE3JtAqJsxVIs1xhhjTFTXN9+cDWs9QZG1AAAAAElFTkSuQmCC"},
    { 11, "Pets", "Domesticated Animals", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QA/wD/AP+gvaeTAAAEcUlEQVR4nO2a3YsVZRzHv4/HsjfbLLctaMNqgzapC7Oydwgh0kuTqLvQiqD6A4reichujW6KbmqXrbQwNuyii7rpwlXXtDKLCs1Aio1W18yV/XQxM3Ac5zzzO8955pyF5gPD4Tzzez9nnteRampqampqamoiAThgAzAJnAD2AI8BC9qwsQB4PNU9AXwDbARclbFHAdhEMe9ZigA0gJEWNjZ1I4dggHtaBJ7xjMHGcx79OeDubuQSBDBeUoDjwBUe/UHgnxIbn3YzJzPAecBsSfAAL3hsvGTQPwmc283cTAC3GoIH+M5j4wejjZWx4jb3zAYuNcpdB1ycb0zbrjXa6DdHVULMAlhtOUnDBe3D6T0LC41ypcQswJ9tyJ7xD5C0tA39qTZkvcQswPeSMMqeKmibM+oiqWU/0i7RCuCcm5J0wCj+R0HbEaPufufcX0bZUmL+AyRpzCBzUtK+gvZ9kmYj+egNJBOZ4yVD2DaPfkcTqUpJk3seGAXeAG5pIfesJ4E54C6Pj6CpNLAqjWkkjXEwVt6ZgzXA0YKA3gHOzsk2SBY+Rbxm8GVeTAGLgHcLZKeB+2MlP9gi+YwPyS1TSZazGzl9SfyI0V+2nM6WwrvT7/nkHbDVE9dRYjwunl+kmQ0dO2o/rkcNcb0ew9G3BkeHgGizM0NMC4HfDHHtjeGsrFfPWN2m3QHgvvQaaFN3tTGmY2W2LPMA6wztTosQsAz4SNJhSdvT6zDwAXCl0Zd1U6Q0dksBDhqdlQ49wB2SJiStk9RoutWQtF7SBHBbDF8ppbFbCvCl0ZnXFnCDpHFJl3jE+iV9BizvxFcTX5UJWAy9Jdsi5+dWN0h2cMYk9RnsXCRpDDgnxFezWyWxdw6wzdDh3OTRf9nYaTXzosfeSoP+1ijJpw6XAj95nG336F4OzAQU4Bie0QH43KN7APA9akFFGCI5oMizC2i5RQW8GpB8xiseu/0ks8Q8k8A11rzaOmkhmew8IOnetOlrSSPOuX9byPcpeV6LdoAsTEm62jn3dwv7iyQ9LCkbOb6QtMU5V7Th0n0Ie/bztOwL5jUkz/50hAJMA5dVFWfsHSFJEnCWpFFJiyOYWyxpC7ll97wGeDPCL59nc6/zKoVkM2RzBclnvE0XV51tAfQBn1SYfMbHJKPL/AFYCxzsQvIZvwPrep23gCXA+11MPM8IsKRXyS8n2QnqNYeA60PzCHrnBrhA0m5JQ6GOI/OjpBXOudIdoDyh84CHNH+Sl5Jj9QdDFEMLsCpQr0osO0lnEFqARrlI1wmKKbQAewL1qmQyRCm0ExxQ0vHEmOvHYFrSkHOu6NjdS9A/wDl3RNLTIboV8VRI8h0DPInt1biqmAWe6HriuSLcDkz0IPkd2M4QqofkpHY9yf5g1exMfUV5cTr629fAsJJ9ujWSblTnr7SdUjLqjEsadc7t79DeaVT6+jnJlPlmSSskXZVeyySdL+nC9FOSZpT05DOSfpH0a/q5U9IO59xMlXHW1NTU1NTU/D/5D8Q7H3ts84ozAAAAAElFTkSuQmCC"},
    { 12, "Toys & Games", "", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QA/wD/AP+gvaeTAAAEAklEQVR4nO2aS2hdRRyHv0lrsb7ahQk2ol1119YWQaUgCq31QYUq1ErBR0QFBSm4EcWF4EY3KiotIhUfuyAUBB/YjeJCSx+SpO1CUYwLH6W2xi5iG5PPxbmhye3MfZx7bk6Se7/NJTP/md9/frlnZu6ZgS5dunTpYELehuo64PHKn++GEI7ViH0Q2AL8DLwVQjibV3deoK5Tx73AuLo2EfuCszmoLp3rnAtFfdOLeSMR+1skdtNc55yiJ2e7ayJluyMDFVgVib02p27h5DVg0ZDXgKkWdSdbbF8YeQ0YbkFTYKSF9uWjXlmZzZtlSn2p7Pxn0so+YClwM9BfKboFeDYS+kDlcxIYCSH8mFdzXqPuSKwC85qOXwUaegTUFcATwHZgDdCXU+8U8BPwDbAf+DaEML+/JepO9VSOCa8RflCfUpeXPc4o6u7KzN1uflHvK3u8s1A3q//NweBn8rm6puyxo/aow3M8+GnOqtvLNuDWkgY/zZT6ipp7n9IoqWVwc7uF6xCA54B96pJ2CqUMWN1O0SYYAPbbxlUiZcDl7RLMwb3AZ+pV7eh8oewEbwcOqLGXKy2xUAwAuAkYUrcV2elCMgCgF/jE7J1kbxEdLjQDIFshngFG1b3qFvWyVjq7CHUQ2JG30xI4DxwGvgY+DiEcbbThQvwGxFgGbAKeB46oX6k3NtJwsRhQzW3AQfXFervJxWoAwBLgZeDtWkGL2YBpnlafTFV2ggEAr6pXxCo6xYCVwP2xik4xAGBjrLCTDOiPFXaSAdHlsJMMiNI1oOwEyqZrQNkJlE3HG5DnutoYsAc4RnZZahfQ0E/PHAwDHwB/AGvJDmivbpPWBdTBxIHFiHpdVWwwfm2uVfaol1Rp9VVyyMNgqwZMqDck4pepQzkTizFk1eBnaG0035ll1IBm5oBDIYShWEUI4TzZV7Uo3g8hTCS0vid7/VUIzRjwd536M60k0mRfp4sSSk2C/0TK1qs9IYTUHcHY4zEGfFknh63AiqqyDalgtQdYH6k6DpyoofNdnTxmiexMPEePJuL71bFGn7uqtrH5ZszEKZA6kMituLfYaq/6b0RkXH248l+Yjl2vnkgkNdCA1mOJtsfNruRPx/Woj9TIq9jlUX0vkZjqqPqpelSdTMT8qV7agM5y9WSij0n1SEXr1xr57Ct08JXEVql/1RCtx64mtB5qQeeM2p7b5+o96rkcSe3NofVODp1z6t3tGPvMxLZVXG6EKfU1Z8wRTej0qK/b+K200xZ8UlwrudXqR9begR1Stxagdad6uIbOhPqhen0RY2vqEpLZ0nQX2TrcR7Y5GgUOVHZohWB2nLUBuIPsus5K4CTZj6MvQgi/F6XVpUuXLh3N/4LZQfQlM+IfAAAAAElFTkSuQmCC"},
    { 13, "Baby", "", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QA/wD/AP+gvaeTAAAD9UlEQVR4nO2bS4gVRxSG//IxzvhYZaNGxpnJJghCBBdCdi4iIRsNqLjQvYgEAllkJbjwAQkJqItsgskQJIIJYjDim8EgQUEQjeAwhBkFRUVdRGKI5nNR3Vpz0923H9WPq/0t+9Y9db7TVX2rq/tKLS0tLW8wpu4EfAEYSR9J+kDSW5ImJB0yxtyoNbEqABYBv/F/ngG7gRl151gawBJgPELeZXfdeeYG2ARMAA+APcAc57PBFPLhSHi3To9cAJ8A/3XIXAc+B/YCj1LIh+yI6qPWiyD2wrVC0rCkxZKQdEfSJUnrJH0lfzmOGmO2dB6c5Sl4JoBhSZ9JWitpUUXdPoo6WGkBgH5JuyRtk9RXZd+STlTc33SAxcDvGeasT8aC6Vab/AgwWZP8OLCwTvmlwJ81yd8EliTlV+qwAEYknZM0WGY/MTyUtMIYM5XUqLQlYs3yknSgm7xUUgEaIC9Jd9M08l4A7G983fKStJkUN0FeCxDIn1f98pK0StLWbo28FaBh8iGruzXwUoAGDftOrnVrUPhn0JFfWjSWZ65Ket8Y81dSo0IjABiUdEbNk78haU03eanACACGZOd80+SfSBo2xtxP0zjXCAjO/Fk1T16S5knqT9s4cwGCMz8mu4nRVFambZipAIF8VRe8xwW+m3qTJXUBHPmhPBll5EdJI5Iu5Py+3xUudvd1oqJb2J+B2UG/c4FTOWJ87FN+iOru548BfR39DwC/Zozzni/5KjczbgEDMXnMAY6mjHMbH9tfQD9wpSTZOL4h5g4OmA0cThFjf2H5oMOdparG8x0wMyanmcBownefApl+oeKqvUDS9hx1y8pPkkY7jm2R9APBhdDFGPNc0r2EePuMMZOFswLWlX+iOYId1jOAgxGf/4J9juDmtSsh3kWc54ZFC7DHu+50juCcYezQ/j6i3XGCCyPwRUK8ScDfEybgW+/Kr5gmn6IIp4GvE+JNYfcg/QHs9+/9kjFgfky/cdMhjingHa/yQSKflmHucAaYG9N33EjoxP+Zd5JY5ln4n4hj3YrwRy3yThJ51uBR3ASGsWv8TiKnA8lX+3KGfUQSy4EnBeXHgbeDeH1EL2enjQTgy9rlnWQ2YN+vKSTvxEssQqPknaQ35yjCU+xucVS8uCLcapy8k/RG4N+MRThOzMoMuwKMuiY0T95Juo4iNEM+hHzT4SgdmxxOvG4rvObIh+BpJGBfYe0t+ZCiRehp+RDyT4feG/ZxkG8kvB7yIZ6K0JvyIQWL0NvyITmL8HrIhwDrSX8DdZmY5XJPg72LPJkgfh/7vn/VL0tHUtqboth/aHwo+xh9QPZ/ABclnTfG/F1Wvy0tLS0tGXgBtI9sAulPU94AAAAASUVORK5CYII="},
    { 14, "Arts, Crafts, Sewing & Party Supplies", "DIY & Handmade", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAACXBIWXMAAAsTAAALEwEAmpwYAAADZ0lEQVR4nO2aSWgUQRSGyxh3AwETxA2CuIBIiIoyQXDBCCGgKCQXRTEXEdccFA/iIXqIS+LFgzuCKIpiwIsQEAUJKBrNQcQFBBUVRUUFFfdPKtOEztg10z1d1VNt+oM6TA31/qrX1bW810IkJCQkJAQDKAM2ASedshEYJSICGAZUOaU4Kt0egAbgE//yEagXhgFWA+9cuq+A+aZ1ewAWA79QI/9bJAwBLAf+eOi+Nz4DgQHAA3Jz35D+QOCpS+c58N31e4MJ3V6ASvwzXWgGqHXZb3Pqql11R3Vr9gFYGsABS4RmgL0u++udunJX3XHdmn0AFgRwwFyhGeC6y75cBA8At111W3Vr9gEYAXz2MfjXwGChEWAQ8DWL5k9ggk5NT4DdPhzQJDQDzMmheUG3ZrYncTFHZ5qFZoAtOTTn6dbMtR2uAe4o9mS5VRUJjQDnsgy+W6dWIIBTik7VaNaRe76KRp1agZBHUEWnzmjUGJtl8G/lvUCXVr6vwyOPjskVu1STRn0WB7To0AgFsF3RuXWa7O/Pcu+o0KERCmA08MOjg7c02b9W0K3PD0C7opOVIe0WKa7eRk6beQPUKTrZGtLuNIXdLmETpJ/UM4+OvpGHp5DBDy9WCtsAmhWdXRbC5kEPey913zW0IC8jimjRpRA2b3rY2yFsBehQ3NTGaLoByt9lwlZIB0y92JaHrRkedsxGfcIi301n4cvkYR621ureViMBaFXMglRAO8cy2neIOABMVVyTjwS0053Rvk7EBaDTwwHyRDfcZ/uhGcfrx7pjDEYBGhWvwSqf7d3h7t4ocGwgnbv74OGAqz7bb3a1kXZGirgBHHKm8V3ghBPXW+izbRPwxFlL9ok4ApSEPbLKJ+933UiwGaDCiR+ukBkc4DBw3imnnd8tMsHp5ACnyJ1AxBnSHy/IRMo98kO+/13ALmB2LLZB0uGxnT7T6EGRKbc2YKKwDWC8zM4C3zDPbycEN9mGgRc7T/wL0SM/jtgDDClkAKSTwnMDGBf14CcpYoCF4kVkOQLSn8jZNHj3hak8Cgdcxl7Omh58LfZTY9IBV7CfdlODL1XkAG1DnkVKTDigmvhQZcIBs1wXGNvLTO0OSOjvACkLprbfkooy7WUjDYkDdEMyA+j3r0CqXy+CCQkJCeI/5C+Xr1Nj9eUFLAAAAABJRU5ErkJggg=="},
    { 15, "Stationery & Office Supplies", "", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QA/wD/AP+gvaeTAAACvklEQVR4nO2bPWtUQRiFn1dFiwiCKPiJX72g1a6ton/AGK0sBEvBRrEVLVXQSv+AmgSLWAqmTCqRpDCCQSRisAhiuoh6LHYDIe7d+biT3N2985R33znzzmHncHf2XshkMpkaY6mEJF0EXpvZSgKtvcAV4BQwFDD0O/AWmDCzP2X78EbSBUm/JT1LoDUiaVnleC/peIq1+TR8QtLSmsmvl9BaNTIF85J2pVxrp4aHJM2sm3hF0pkILZM0l2jxq9zdiHWvbfhlwcTfJB0I1DuZePGS9ME175Z4C7gFXCr4bD8wLml7gN6xEr0U4cyBKAMknQPuO8qaQEgohpiVTDPYAElHgefAVo/yqyoRipvBtpBiSUPABLAnYNgTSbNmNhXUWXceAtMJ9dy0Q+9FZBgtSjro0B8O0BtOta6QLXAbGImcZx+tUNwROX7D8DKgHXr3Ss7VAJ6W1EiO04DA0HPRc6HoE4JFofcRmOkybjdwtsP1x5KmzazbWBcNSV6FZjZWYh4oCKElSUcc40zSK98QCwxBb1zri70TvGNmX7oVmJmAa5H6m0asAT98iszMq65KyvwWGAiyAVU3kJAx64Br0CAZEEU2oOoGqqb2BgSdB/Q4TUmj6y+aWdGxHTBYBhwCgs8Jar8FsgFVN1A1/ZoBU8DXFEL9asCj0gcdbWq/BbIBVTdQNbU3oF9DcNTjvBMA15lA7b8B2YCqG6ia2hvQryHYiWlazw0EMUgGLMTcHtd+C2QDqm6gagYpAw53+tvdlQuDZEAD+O9UGMcT8XkLRI672enrVpJfifW8NGMNaEaO68bnDdCcdxX00haYBeYSazpvjHrGgPYzRTeAVK+6fAIeuIp6xgAAM3tD612hnyWl3gHnzWzZVeiTAUmOn9exUPSBmY1JmgQuA6eBnQG6i8AkrZem/pZrMZPJZGrAP+s7Gd91ZI+yAAAAAElFTkSuQmCC"},
    { 16, "Tools & Home Improvement", "", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAACXBIWXMAAAsTAAALEwEAmpwYAAABXUlEQVR4nO3ZS0oDQRSF4WtwB451Az424QIEwQX4GOoiIg5EJ0EXYISMegO6EjfgRB05iRPRX4q0EIhCNanursf5oCcZ1T251VT1NRMRERGZAwyAa+CN+Lk1Xrk1WyjACek5ChnAPekZhwygIj2VAgiFxDsAOAUugO1SA6jq376BW2C11AB+3ZQewFej7UB+ATjD0gOYlB5ApQBKOQoToAOOSc9hyAAG9RXzlfi9AJfz1+GlA0idAkAdUGkLLNI7wGIBrAFnwF29X0M/z0sdhdsE7APvdG8YQ/G7wGcPxbvr8Fbfxa8AT/Rj1GvxDrDT0z8/avxJrA3A3j+LbOMlOAHOgU2LBXDwV/VWChQA6gC0BRZZ7oAN4BH4oKv5fkyYFd/tfD8mwLTz+X5M8BfPdTUkBeBPHWA5Qh3gTR1gOUId4E0dYDlCR2Eems73swKsMwth6jvfFxEREbEO/ADiFbekRtGUMAAAAABJRU5ErkJggg=="},
    { 17, "Motor Vehicles, Automotive Parts & Accessories", "Auto, Tires & Industrial", "data:image/png;base64,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"},
    { 18, "Beauty & Personal Care", "Cosmetics;Health, Beauty & Personal Care;Hygiene", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAACXBIWXMAAAsTAAALEwEAmpwYAAACPUlEQVR4nO2bP2sUQRiHXzQQ0ZDUgiKSKkQFEVSMprFKUBCiXyB+A8FCFIxKUgf/1CpcCDlioZV2iaCVtYX4AQxaREVBk/jIkCHIMXuJzO7M7M77wFbHzu+d52bn7t7bFVEURVH8AU4Dbc/jAXAJ2CV1A7hCebwDDknGAgwfgH7JWIBhSjIX8F4asAn68EvqDp5I3UEF+CF1BxXgh9QdVIAfUkeAfcBRYAx/xuxYeyV1gIvAC+An5WPGfA5ckNQABoHXhGMJOCwpAIwCXwjPZ+Bs7MkPAavE4xtwJNbk9wAfiY/pG/TGEHC9oKAN4AlwxnwalPSJMgI8Bf4UZF4rZ1Y7BNgNrDgKWQMmpCKAyzajk09B+4jAuYJ34laA7NsF2SNVZ28B3HQU8KOMJb8dQF/B94wbVWdvATxyFLAkgQCWHfkPJWABC44CFgPmLzryFyRgAW1HAe1c8iV2AbHzpYRubxWoANEVEAj0EkD3AMrF/MiZBybtMQes57IJ/gbGHRnn7WuNFzDVJeduDgIOdMk5mIOA3m26To0XcLxLzokcBLS75DzLQYDhMTDwz/gDtq9IUwTMA1eBadvKdmHa6y+BV8DX/xw/aQHTHeeeLGhs+pKsgP2O89/kLuBtTgJmOs49ldslgG2imk1wBvhONSQtIAQqQAKugDnSoxVSwD3S405IAcfs3+CpsBH8Rgk2H29JhdmgkzcAPcD9yCvBZM+aWiQWbN7DZ1pXrRIemtrp0bKZw9EmriiKIg3gL31Q7N9UOef0AAAAAElFTkSuQmCC"},
    { 19, "Drugs & Medications", "", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAACXBIWXMAAAsTAAALEwEAmpwYAAAC6ElEQVR4nO3by4sUVxTH8Ts+QAUFYYIzEtC9joriRrJOVq4kW0MIGh0JulCI+FgmvhbR1WShZi36B6gkoKIEdOljkWXMBDOObrJQfHzkMtWh7ame7sxUVVd31Xdf99zfPefcx7m3QqipqampKR8YwS4cwmlcxHkcxVfYgKEwSGAF9uN33fEnzmB96GewGPvwj/nxBhMYDv0GPsUt2fAMn4d+wUwexzDOkrcYD2UHWzHdhaCnuINruIFHeNfFd+P9LP5fnMLmNt+vwV780SESvgh9KP5KFNhlW0txEK/nmBOG+0X8exyfz9qOzzDVpt2JUAawBc/nEP/dAtvfgVdtlsh12SnJx/MHMrIT0yGNH7Jov5Seb7G1BE9S7DzMykYpPd9ic08be+sHXnzTISptn7A7DLr4BnicYvf7MGg53w7cTLH9Uxh0zzdIts2tXAqD7vkGuJvShx9DD7e3R3IzPrsvQ5hM6cPBXp7q7mFVLh1Ij8Q0dvbySFvYICT1w1biFnllkTnfjgdYnWlHPu7TaHKUbuV6Lz1fSCQkuX9VOnvLIj63QcAJ6fyNZb0M+9zTIakOxaU2jW/K5PnMIyFuruYQ/ysWZSF+LAfxCx6EDuJjtXk0q7r9XzmJn/cgdBD/AhuzurG5nbP4/z0IXYjftmDxkVhbVywdJ8YOE95LbA8ZXlROKZ62kVCY55uM9YpZg1Co+Aju6y3/pUNhYd8Aa5WDGAlHCvV8BF8qP/mIj+CwcpN92DeDs6oqPoJflDfst4a8wQVV9HwDHFNV8RF8rTxMFxL2zWCTKnq+QSwiFHAELp/nm8G5yoqPxPv05HlJNcI+DfxcOc83g0+Sp2bVE98gPjbs8mXm4IlvgG8rkfNzkVRkso6EyXbPYUuJmXTIak74LRZeQr+B4WR1mO8S+SwpcS38xqYE+4RzyXP2TrxPfoOJv8MsD4OEmWvpscSrsZByOXnxHaPkZFJeG+l1P2tqampqwmw+AO2Rw/WiIGDFAAAAAElFTkSuQmCC"},
    { 20, "Sports & Outdoors", "Sporting Equipment;Outdoors & Camping;Hiking;Hunting;Fishing;Biking", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QA/wD/AP+gvaeTAAAEPElEQVR4nO2a34sVZRjHv0+aGbEJ/boo291ItwQTFOumGyP6edWvTQsCY8OLCrzrOnRRwrv+AV2NfghhGwTSTd0VsSW1IpFFF5ViJbWK7rrqfrqYM3Cc887sO3Pmnfdo53N1ZuZ9n+/zPPP+mHnmSH369OnzP8ZiO+ACuF3SS5LWt059J+kDM/s7nlcNAWwGztDJDDAa27+gAE8AlxzBp1wCHovtZxAAA34sCD7lGNCTU7crgHUewaesrUv3uroM1cBwibb31CXaSwn4t0Tbf4J5EQvgxpzVP8sMsLwu3Z4ZAWY2K2mPR9N3zGwutD9RAJYA7xfc/feAJbH9DArJdvgy8CVwtjUtvgC2XDPbH7AM2AH80bqzl1v7+5bYvgUHWAMcKRjmb8f2MRjAg8BfHiv99ti+1g7wCH7bXDolnovtc20AzwMXPINPOQc8FNv3rgFeAOZLBp9yErgrdgyVAUaBixWDT/kKuCF2LKWpKfiUidjxlAJ4scbgU96MHZcXwDMUV3WqMg9sqtvfWh8tgfslTUm6qaKJI5KWS1qTc31G0m5J+yTNF9g5Z2ZF18MAfNLFHf4cGABWAr92OVqaL54Ct1B93k8A17fZuhc40UQC6qwHrJK0tEK/dyVtNbOL6Qkz+0XS45JO1+RbLnUm4GzJ9pclvW5m282M7EUzOyrpaUln6nAuOCTFjDJzd8zT7kZgKtQUqHsXeFbSx552j0p61Mz+9LQ9JGlI0jKP5tNmdsrHbu0Ar5C8yPgwDdwRxdGQAIPARyWScGtsn4MAbAK+90jCZ7F9DQawFHgDOL1IEh6O4V/pRRBYIelJSWslrWyd/l3StKTDZubctoDbJI1Lek2Sq7S9x8zeCqXfNcAwcIDiys4FYD/Jip1nZz1w3NH3wyb0qwa/DZhbZAi3M0vBPg8cdPQ52JR+2eB3lRDOMt5tAkLolwl+W47hBeAbkpeYidbvhZy2HXfCNwGh9H2DH8Y97A4BqxztVwOTjvazwGDZBITU903AAYexcQq+z5F813MN2X0VEhBM3yf4FXSutoeKxDNOZO/EHDDgm4DQ+j4J2JwxsIBj2BX0H6FzTo62XV8sAUH128mrBzyQOZ4ys599HTCzn5T8ubGddb79m9TPS8CdmeNjvuIFfbI2i2hMPy8B2QpNlbpBtk9H1aeAxvTzEnAyc5xXpi4i2+dEib6N6ecVMX/IHG8EVpvZcR9l4D5JGwpsfu3o1n4utP6iBm52bEOTJbahT7vZhmLrp4YmHFvVriInWuK7Hf32lhLvAX0BQySPkVkmgRFH+xFH5gHOA3dfbfqp0TGHQUgeMqZI3r33A9+S/zLyaiXxHtBPnRjPMezDzq7Ee0A/dWIM93DM4zywtRbxHtBPnRgkWZiKKjNzwF6qzrkI+lWKogOSntKVRcnflHzpOWxmZb8RXlX6ffr06XNN8R8f+FLdSRxelgAAAABJRU5ErkJggg=="},
    { 21, "Real Estate, Property & Housing", "", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAACXBIWXMAAAsTAAALEwEAmpwYAAAC4ElEQVR4nO2ZPWgUURDHN1FEQQ0RIxiRoE0g2IiNgfRaGBRjSLAINn4UVkGwUJtUIY2VgYhgJ3jgV6EgEQIWNqIighFUEFQQsdDgF8b4k4ezOLfs3u3d7t7t5uYHw3HzZt6+98+8j9t4nmEYhmEYhgIosfwoeXHBBMAqgOWHLQHP9oB0NsF5YBToktiNwBjwpkLOe2CX2JGImN8qZrBKOe9TsWE2l9USeAasj8jpAl5H5E2ruJXAp5CYRRWzrYoAPVXGfyMrAQ6omL3ARfepfCMReXsC/V9OSwDgKHAsYE+yEqBb2lcD38X3DVgr/nUhOZ+BVYH+96cogFs6cUhFgC3SvgL4qPxXgRmx4ICuqH4H5HMN8LWIAhxSMTuB+zEePCLxG9zaVPnXiyjAS7frB2J3A7cj4n/6myZwEPjiNkH5PpaGACFjP5elAMhxNxiS4yb0i3LuqPYL4utXFbFYRAF8HgNDgbwpyjmu2l6I76zy3UthCdwFZpW9avRNcEblbVX+JWCzatsutkn5ThZpD5hV7e6s1ehJ+cvgQYznOMH+FEWAd0C7GuCC+D+oja1DxZ9W/Q2578r6VNvDogjgGFUx3e5m6N8NxHeY//Qq/1vKmVJtZ0IEaAc6A9YTIUBniN0kIwEWgtdalbNDqsHxXPl7Q/p5pNr7ggJE9N9Rw2+BUtab4BxwSu7+J4Brcub7PAUmxW6F5C/JieHH/BDfZAU7r/Knq8TOZy1AETEBPKuAmGBLgJbfA8alCrKy4L0A8WX5zHEvL5D0nC46mABYBWBLoMB7ANCmXnFVJGkFxHkGcMn/qZ6ryTsaJEBjRKDGyTdYgGxFoI7JN0GAbESgzsk3SYB0ReDf5N2/vOoios9+YDhg/SkKgIy5rWl/eZ9EA0gmQLJKIIXJ50CA+kQgpcnnRIDaRQAmUnpwXgRwTDTrhchwQksLeyfoNakC8oIJ4FkFxIRWXwKGYRiGYXitwF+FAy8M28uvbgAAAABJRU5ErkJggg=="},
    { 22, "Luggage & Travel", "", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QA/wD/AP+gvaeTAAAC9klEQVR4nO2bPWjVUBiG38+K2C7iLzhZVyc7O/iDojhY3HSxautYFQQXF0HB2cEiKCLqIEoFCwoiaKU4V0REKFpxrFY61EFrfRyuQr3kJLnJPTkxNw90yTnN95435+R+J/ki1dTU1HQw5uOkwFFJ+5sOz0gaNjN8xCwVwAGiORFaWyEA3cB8hAFzwMbQ+goBGHXMgjuhtRUCcMRhAEDz/aF6AGuABYcBU0B3aI3eAZ7FzIKLofV5BzgVY8B3YEtojV4BNgG/YkyYALzkIqUBmIwxAGAotEavAOcTDJgFNoTW6Q1ga4IBALdD6/QK8CGFCXtCaFtWUJyxFH1GqGpuAOxMMQMALoTW6gWgC/icwoDCc4PIJQAMAveW/A3mCWJmi5Iep+i6QtJVQucGwLGmK7MAbMt5zoMplwF5Dc8NsDlC1CdgXY5z9gDfUhoQPjcAPkYIe0SO6Qk8bGEW3GrneLKIvekQdibHOY+3YADA7naOKYrlMW3jkgYijl8C5iV9zRBvZYv9R4BzGeL8kDRtZq+TOjqnM9AraTpD8DLxTtJJM3vq6hC7noFpSb3tVlUwi5IOm9n9qMakVHi8/XoKp0vSNRy/YEkGvGi/niCsknQoqqETZsBf+qIOFrUbLAORr+SSDNjhQUgoJqMOJhmw3YOQEMxJuhvV0AkzYFHSkJnNRjU6DfiTCP3vOcBbSXvNbNTVIS4Vdl39BUnDypYKr5d0pYX+U5KypsLvzexNhv9t4GkzNFi2zVCcWB/b4bEWBh9uO0wHPRBx3QSb1/9PNTYUX3LE2iepJ2Xfs2Y2kyNWalw3wWWSlu6enpjZy5yx+lP2m5B0I2esckGJH4sXArAr5dqv7IuRyykGX92yGUr8ctQ7QF+KwVf39Th1gQSvEgyobokMjSKpOKpdJAWcjhl8NX/zlwI8jzGg2oWSwFo6uVQWGIi5+h1RLP3AMfjql8vT6R9MAP2Oq1+6T2biHormYbX+fZ4gNT6auu4pXk1NTU1NFn4DHMdp490i7dkAAAAASUVORK5CYII="},
    { 23, "Business, Industrial & Scientific", "", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QA/wD/AP+gvaeTAAADDUlEQVR4nO2ZvWsUQRyG30lSaCJiVLSKYAoxooJIIIWiWImFYJcEYmnhPyD4B6iNpcFCUAjEkAQsRC20ERTxA4JFijSCImgR/IhJUHPJY3GJKN7uzsztZO5knubgbnbe9/fu7MzsnJRIJBKJRCLRwABbgBd4ENt73dRTvE0AbY5mdknqltQpaVbSlDFm3q80K71OSQ8lHQ6lYWOiFTgLvK4R8BJwBzgUQLcTeOV7521HQJGJrcAjC50KcKGk2ksr3iaAzEcA2CDpnqQ+C8+tkq4AFWPMVftS/9JrkXRK0vHVz56MppOSxn00XA1d8gj8J7DfQ6sLeG7R/xjgNG95QXXoL3gEAHDbUWsTMN0wxa+aGvIsPhTjBCq+JeP7eMvOv0xIGjTGVEJ0nhXA9hBiHjxVwOKl7AAWQgk60iepP6RAVgAzIUUdaJV0CxgIJWBqfQn0SJrO+r2AKUmXHdp3SLomqT2nzbKkIWOM0wpTF8B9zxn7tIfWGYqX3QowGKLWLFPdwFfH4icBn1EjoAe4CbwFlhslhKPAF8viPwB5w9hF9xgw7xh+Tcowsxu4C6wUaK0A+0qof023lBDK8iNgDzBcoHe9NEGVE0KZfgS0A7M5eovAtpI1jwBzoQLI2gfUxBizKOlGTpONks659Gmh+UTV1+NvZfb7u3/XC4AuSW+UfZbwXlK3MWapHmM1dA9I2ut6nTFmokwfa2bGCkZesJ1bQwD0FgTwMrbH4ADPCkKwOUprXoD+ggDWb98eA6ANeJcTwBLVCbOhcVoG/2T1kGI4p0mbpPO+/TcFVM/v83Zqn4CO2D7z8B4BkmSM+SxpJKdJp6ShejQaHqrvCFmvrwAzVP/0+H8BHhSsCCdje6wb4CAwCnwsKHa9mQceAwN4HsbYFD8I/Ihaph0jlP24Ub3zzVD8Ghdd6iscMsCopGZ6uZmTtNMY892msc1wOVGfn3Vns6Re28Y2Aezw9xINa882AYSZWcNiPRH+3xsUC1IAsQ3EJgUQ20BsUgCxDcQmBRDbQCKRSCQSiUQsfgGI7rZpsWTP5QAAAABJRU5ErkJggg=="},
    { 24, "Illegal", "Banned and/or prohibited items", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAABmJLR0QA/wD/AP+gvaeTAAAFDUlEQVR4nO2bzW9WRRTGn2ljEaVFSghl40fStC5cYcNOSXVjQmo0fqAsWGI1oWyQmFQihkDUFQQ2xqVGoqa6smGPfwENkmoMpUHBapR+CG2I/bmYt0rrmfs5975NeJ/lvTPnOee5c+ecOzNXaqGFFlq4h+HqIgK2S3pCUr+kRyQ9JGlT4/aCpD8lXZX0g6QJ59xMXb5VAqANeAY4C3xPflwCzgCDQFuz48kMYCvwHjBdIOgQrjZsdjc7viCAzcBHwHzEwNdiHvgQ6Gp2vKsA7AOuVxj4WvwCvB7D91KTYONJfCLp1RzdFiRNSbohaV5Sm6QHJfVI6pV0fw5b5yS94Zybz9EnDoDHgR8zPK1FYBw4DOwkYULDT5z9wAFgrNE3DZNAX52xC9gF/Jbi2AzwPj79FeXZAozgJ8E0roGYMSY5tYvkie4WcATIM5TTODuAg8DNBN65ykXAD/ukJ3+BCocj0IN/nZJGQjX8QBfJ7/wyMFQJ+Wo/HDDa4LMwCXRWQfxFQvArWAT2RCe3/dkP3An48Xlssn0Zgm+WCKGRsDcWyWbCRU6IvE4RRgM+/EyMVwFf3lq4AAwRztW1iICvHUIT48myxrdip7xbNGZbYM86EKEHO0XOUeYDCjgWCOztNe3WgwgjAf6jRQ22YX/SzgAbjfbPAbcDTiwBz5eOMtnf+4Apg3uKIusJwLOBYI4l9GnqSAAOBbh3FzF21jB0m5TavpkiAN0B7tNFjFnLWOMZ+zZThG8Mzom8RrZj5/jDOWw0RQRg2OBbBrblMRJ6/3fmdKZ2EfAfbBYG8xh5yzAwT4HZtG4RgHbsbDRstQ8F9Khxbco5t5zXIefct5JekrRk3N4gaSymCM65vyX9ZNyyYgoKYK26Xi/hVK0iSLI2VTZbDUMCbDKu/VXYHf0rwguSFo3bGyR9TbxiyVoktWIKCmCh9Daac+68pBdli9Ah6atIIpC1YUiABeNalFWWhggvy34dOiR9GeF1sJ62FVNQgDnjWvY8moIa5oQdxrVZq2FIgCnjWm+RNBhCVSIA7QpksTxGQoVQf16HMnBFrROAgYCtXIVQqBQ+kDvCbHzRRMDvSaxFvlK4YeiSYWgsd3TZ+aKIAJw3+l8s4tCZgCNbchvLzllKBPzSmNX/VBFnBgOOjBSOMBtvYRGA44F+TxdxxAFXDGPTQEepKNO5cy+vAQ9gb9tNAcWKOPyxFAsHS0eZzp1rJADvBNoWWxRtGO3GLy2vxU2gp3SU6fyZRMCfKbBGzCxl5yzgg4AD49RweiuDCEPAd4H7J2I40IU/k2NhNEKMWXxIEiG0PXeNWLvEwGsJ5PujkKT7kCSChVdiO3AuQHRnHYrwaRXknfjDB6GRMErRdJPPjyHCwx7gMmAufsQg78NvjYUwToXZAT/bhyY8gF+B3qr4V5wYwE6NK7iJ36iMViwBG/F5PlQcgU95T8biTHNoIGUkgK8YD1Fiexpf2x8n/UjejdqCv8u5PsJzwt1YxG9XDeM3LdoTbLY3xD2C/6rLMuFdpsSwL3tUtlPSx5LynNtdkl+3Xzkqi/x64w5Jj0n639Z7Aj6T9KZzzlzvqw3AXvyZnLpwjdh5vizwafIkyRNkWcwCJ6jiHGAs4D+gjmKf1iiKK8C7VLgYEx349YTdwGlgguTiZS2WgYvAKeApKiyw6vxpapv++2nqYUndWv3T1B+SpiVNyv809XtdvrXQQgst3LP4B1dCXq0t0BR7AAAAAElFTkSuQmCC"},
};

const std::vector<Subcategory> predefined_subcategories = { 
    // For each category is a subcategory (for example, the books, movies, and music categories can have the digital goods subcategory if they are digital rather than physical)
    // Digital Goods
    { static_cast<unsigned int>(predefined_categories.size() + 1), predefined_categories[5].name, predefined_categories[5].description, predefined_categories[5].thumbnail, 7 },
    { 26, predefined_categories[5].name, predefined_categories[5].description, predefined_categories[5].thumbnail, 8 },
    { 27, predefined_categories[5].name, predefined_categories[5].description, predefined_categories[5].thumbnail, 9 },
    
    // Illegal
    { 28, predefined_categories[24].name, predefined_categories[24].description, predefined_categories[24].thumbnail, 0 },
    { 29, predefined_categories[24].name, predefined_categories[24].description, predefined_categories[24].thumbnail, 5 },
    { 30, predefined_categories[24].name, predefined_categories[24].description, predefined_categories[24].thumbnail, 6 },
    { 31, predefined_categories[24].name, predefined_categories[24].description, predefined_categories[24].thumbnail, 7 },
    { 32, predefined_categories[24].name, predefined_categories[24].description, predefined_categories[24].thumbnail, 8 },
    { 33, predefined_categories[24].name, predefined_categories[24].description, predefined_categories[24].thumbnail, 23 },
    { 34, predefined_categories[24].name, predefined_categories[24].description, predefined_categories[24].thumbnail, 19 },
    
    //{ 0, , <category_id_goes_here> },
};

//-----------------------------------------------------------------------------

inline const Category& get_category_by_id(unsigned int id) {
    for (const auto& category : predefined_categories) {
        if (category.id == id) {
            return category;
        }
    }
    throw std::runtime_error("Category not found for ID " + std::to_string(id));
}

inline std::string get_category_name_by_id(unsigned int id) {
    for (const auto& category : predefined_categories) {
        if (category.id == id) {
            return category.name;
        }
    }
    return "";
}

inline std::string get_category_description_by_id(unsigned int id) {
    for (const auto& category : predefined_categories) {
        if (category.id == id) {
            return category.description;
        }
    }
    return "";
}

inline std::string get_category_thumbnail_by_id(unsigned int id) {
    for (const auto& category : predefined_categories) {
        if (category.id == id) {
            return category.thumbnail;
        }
    }
    return ""; // Or some default thumbnail if category id not found
}

inline int get_category_id_by_name(const std::string& name) {
    for (const auto& category : predefined_categories) {
        if (category.name == name) {
            return category.id;
        }
    }
    return -1;
}

inline std::vector<Subcategory> get_subcategories_by_category_id(unsigned int category_id) {
    std::vector<Subcategory> matching_subcategories;

    for (const Subcategory& subcategory : predefined_subcategories) {
        if (subcategory.category_id == category_id) {
            matching_subcategories.push_back(subcategory);
        }
    }

    return matching_subcategories;
}

inline int get_subcategory_id_by_name(const std::string& name) {
    for (const auto& subcategory : predefined_subcategories) {
        if (subcategory.name == name) {
            return subcategory.id;
        }
    }
    return -1;
}

inline std::string get_subcategory_name_by_id(unsigned int id) {
    for (const auto& subcategory : predefined_subcategories) {
        if (subcategory.id == id) {
            return subcategory.name;
        }
    }
    return "";
}

}
