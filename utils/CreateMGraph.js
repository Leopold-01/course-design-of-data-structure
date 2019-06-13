//TODO:放弃用模块化
//不知道用模块化对传入的数组处理 让返回的数组改变

//根据图中的数据建立 邻接矩阵 
//先建立下三角 999999表示不可直达,然后对称到上三角,对角线置0
'use strict';
function CreateMGraph (MGraph,n) {
    //js不用定义数据类型 弱数据类型 根据你所赋值的类型决定是什么类型的数据
    var i,j;
    //js的二维数组初始化
    var MGraph = new Array(n);//n为矩阵行列数 即图的顶点个数
    for(i=0;i<MGraph.length;i++)
    {
        MGraph[i] = new Array(n);
    }
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            MGraph[i][j]=999999;
        }
    }
    MGraph[0][1]=2553;
    MGraph[0][2]=700;
    MGraph[0][3]=704;
    MGraph[1][2]=511;
    MGraph[1][4]=812;
    MGraph[2][3]=349;
    MGraph[2][5]=1579;
    MGraph[3][6]=651;
    MGraph[4][5]=2368;
    MGraph[5][6]=1385;
      for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            if(i==j){
                MGraph[i][i]=0;
            }
            if(MGraph[i][j]<999999){}
            MGraph[j][i]=MGraph[i][j];
        }
    }
    return MGraph;
};


//这里用export.CreateMGraph=CreateMGraph;会报错 试了下module.export没错
//下次暴露函数的时候用module.export 或者以后都用module.export
// module.export.CreateMGraph=CreateMGraph;
module.exports = CreateMGraph;