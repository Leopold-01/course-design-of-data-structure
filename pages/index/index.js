//TODO：用户点击查询后 先获取前端用户输入的地名 
//将地名转换为矩阵中的数字(用js的对象模拟字典（键值对）的存储结构)
//Map键值对存储可以方便的将地名转换为对应下标
//微信小程序中使用Map无法用get set方法获取数据 所以自己模拟一个

//require就是在nodejs在找有没有可以引用的
const posS = require('./position.js')
//放弃使用模块化对数组进行操作 还不会
// const Graph = require("../../utils/CreateMGraph")

Page({
  /**
   * 页面的初始数据
   */
  
  data: {
    //获取城市名对应的邻接矩阵下标
    pos: posS.m,
    //获取用户输入的地名
    start: '',
    destination: '',
    //初始化图的邻接矩阵
    mGraph: [[]],
  },

  //拿到页面用户输入的目的地
  formSubmit: function (e) {
    console.log('form发生了submit事件，携带数据为：', e);
    //这里的传来的数据要先存储一下 再在setData中赋值 不然报错
    //Cannot read property 'value' of undefined;
    const start1 = e.detail.value.start_input;
    const destination1 = e.detail.value.destination_input;
    this.setData({
      start: start1,
      destination: destination1
    })
    //测试成功将用户输入的地名存储
    // console.log(this.data.start)
    const num = this.data.pos;
    console.log(num[this.data.start])
  },
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    const num = this.data.pos;
    console.log(num);
  },

  minDistance: function () {
    console.log("minDistance")
    //TODO:按照图创建邻接矩阵
    
    var Graph=this.CreateMGraph();
    console.log(Graph);
    //TODO:Dijkstra算法解决单源最短路径问题（迪杰斯特拉）
    console.log(this.Dijkstra(Graph,6,5));
    //TODO:Floyd算法解决单源最短路径问题（佛洛依德）

    //TODO:在界面中渲染出来最后结果 
    //将最后计算的结果存储到data中 
  },

  
  CreateMGraph: function() {
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
  },

  //distance中存储的是目前从源点到每个顶点的间最短路径
  Dijkstra: function(matrix, start ,destination) {
    const rows = matrix.length,//rows和cols一样，其实就是顶点个数
        cols = matrix[0].length;
    var s = new Array(10000);
    var dist = new Array(10000);
    // var path = new Array(10000);这里暂时不需要path
    var mindis,i,j,u;
    if(rows !== cols || start >= rows) return new Error("邻接矩阵错误或者源点错误");

    //初始化
    for(i=0;i<rows;i++)
    {
      //存储源点到所有顶点的目前最短路径长度 所以初始时就是为源点那一列矩阵的值
      dist[i]=matrix[start][i];//距离初始化
      s[i]=0;//s[]置空
      
    }
    dist[start]=0;
    s[start]=1; //源点编号start放入s中
    for(i=0;i<rows;i++) //循环直到到所有顶点的最短路径都求出
    {
        mindis=Infinity;//mindis置最小长度初值
        for(j=0;j<cols;j++)//选取不在s中且具有最小距离的顶点u
        {
          if(s[j]===0 && dist[j]<mindis)
            {
              u=j;
              mindis=dist[j];
            }
        }
        //找到最小的u
        s[u]=1; //顶点u加入s中
        for(j=0;j<cols;j++)//修改不在s中的顶点的距离
        {
          if(s[j]===0)
            {
              if(matrix[u][j]<Infinity && dist[u] + matrix[u][j]<dist[j])
                {
                  dist[j] = dist[u] + matrix[u][j];
                }
            }
        } 
    }

    console.log(dist);
    //返回源点开始到每个顶点的最短路径数组
    // return dist;
    //返回从起点到终点的最短路径
    
    return dist[destination];
  },


  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {
    
  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {
    
  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {
    
  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {
    
  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {
    
  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {
    
  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {
    
  }
})