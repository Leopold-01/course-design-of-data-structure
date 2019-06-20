

  // 三种不同查询寻求 创建三种不同的邻接矩阵
  //Distance
  const CreateMGraphDist= res=> {
    //js不用定义数据类型 弱数据类型 根据你所赋值的类型决定是什么类型的数据
    var i,j;
    var n=7;//图的顶点数
    //js的二维数组初始化
    var MGraph = new Array(n);//n为矩阵行列数 即图的顶点个数
    for(i=0;i<MGraph.length;i++)
    {
        MGraph[i] = new Array(n);
    }
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            MGraph[i][j]=Infinity;
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
            if(MGraph[i][j]<Infinity){}
            MGraph[j][i]=MGraph[i][j];
        }
    }
    return MGraph;
  }
  //Time
  const CreateMGraphTime= res => {
    //js不用定义数据类型 弱数据类型 根据你所赋值的类型决定是什么类型的数据
    var i,j;
    var n=7;//图的顶点数
    //js的二维数组初始化
    var MGraph = new Array(n);//n为矩阵行列数 即图的顶点个数
    for(i=0;i<MGraph.length;i++)
    {
        MGraph[i] = new Array(n);
    }
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            MGraph[i][j]=Infinity;
        }
    }
    MGraph[0][1]=6;
    MGraph[0][2]=4;
    MGraph[0][3]=3;
    MGraph[1][2]=3;
    MGraph[1][4]=3;
    MGraph[2][3]=3;
    MGraph[2][5]=4;
    MGraph[3][6]=1;
    MGraph[4][5]=8;
    MGraph[5][6]=9;
      for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            if(i==j){
                MGraph[i][i]=0;
            }
            if(MGraph[i][j]<Infinity){}
            MGraph[j][i]=MGraph[i][j];
        }
    }
    return MGraph;
  }
  //Cost
  const CreateMGraphCost= res=> {
    //js不用定义数据类型 弱数据类型 根据你所赋值的类型决定是什么类型的数据
    var i,j;
    var n=7;//图的顶点数
    //js的二维数组初始化
    var MGraph = new Array(n);//n为矩阵行列数 即图的顶点个数
    for(i=0;i<MGraph.length;i++)
    {
        MGraph[i] = new Array(n);
    }
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            MGraph[i][j]=Infinity;
        }
    }
    MGraph[0][1]=321;
    MGraph[0][2]=332;
    MGraph[0][3]=266;
    MGraph[1][2]=253;
    MGraph[1][4]=123;
    MGraph[2][3]=344;
    MGraph[2][5]=496;
    MGraph[3][6]=60;
    MGraph[4][5]=483;
    MGraph[5][6]=555;
      for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            if(i==j){
                MGraph[i][i]=0;
            }
            if(MGraph[i][j]<Infinity){}
            MGraph[j][i]=MGraph[i][j];
        }
    }
    return MGraph;
  }

  //选择函数 根据传值选择创建那种矩阵
  const ChooseCreateGraph= index => {
    var Graph=[[]]
      switch (index) {
        case "0":
          Graph = CreateMGraphDist();
          break;
        case "1":
          Graph = CreateMGraphCost();
          break;
        case "2":
          Graph = CreateMGraphTime();
          break;
        
      
        default:
          break;
      }
      return Graph;
  }

  module.exports = {
      ChooseCreateGraph : ChooseCreateGraph
  }