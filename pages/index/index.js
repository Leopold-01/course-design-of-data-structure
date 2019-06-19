//TODO：用户点击查询后 先获取前端用户输入的地名 
//将地名转换为矩阵中的数字(用js的对象模拟字典（键值对）的存储结构)
//Map键值对存储可以方便的将地名转换为对应下标
//微信小程序中使用Map无法用get set方法获取数据 所以自己模拟一个

//这里这么做也只是方便了读取城市名字对应的下标时不用遍历数组获取而已  
//正常使用中还是要创建对象数组然后遍历的  因为键值对应的数据不光一个下标 还有canvas中的位置坐标
//所以这里另外用一个对象数组来存储 城市的canvas坐标
//写在position文件中 这里引用
const coord = require('./position')
const Coord =coord.Coord;
//require就是在nodejs在找有没有可以引用的
const posS = require('./position.js')
//放弃使用模块化对数组进行操作 还不会
// const Graph = require("../../utils/CreateMGraph")
//作为全局不用来回传值
//path保存源点v到图上其它点的最短路径 path[i]表示v->j的最短路径里j对应的上一个点
var path = new Array(10000);
var result = '';
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
    //要赋初始值
    matrixStart: 0,
    matrixDestination: 0,
    //初始化图的邻接矩阵
    mGraph: [[]],
    isSearch: false,
    imageW: "",
    imageH: "",
    //记录当前页面要查询的内容
    lookforwhat: "",
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
    //因为第一个input输入后 点第二input不知道为什么就直接提交表单了 所以这里第二个值赋值会报错 所以判断下再赋值
    if(num[start1]>-1&&num[destination1]>-1){
      this.setData({
        matrixStart: num[start1],
        matrixDestination: num[destination1],
      })
    }
    
    console.log("matrixStart:"+this.data.matrixStart+"  matrixDestination:"+this.data.matrixDestination)
    console.log("minDistance")
    //TODO:按照图创建邻接矩阵
    
    var Graph = this.ChooseCreateGraph(this.data.lookforwhat);
    console.log(Graph);
    //TODO:Dijkstra算法解决单源最短路径问题（迪杰斯特拉）
    console.log(this.Dijkstra(Graph, this.data.matrixStart, this.data.matrixDestination));
    result = this.Dijkstra(Graph, this.data.matrixStart, this.data.matrixDestination);
    //TODO:Floyd算法解决单源最短路径问题（佛洛依德）

    //TODO:在界面中渲染出来最后结果 
    this.DrawCanvas();
    this.setData({
      isSearch: true
    })
    //将最后计算的结果存储到data中 
  },
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    console.log(options)
    this.setData({
      lookforwhat: options.id
    })
    console.log(this.data.lookforwhat)
    const num = this.data.pos;
    console.log(num);
    console.log(Coord)
    //在页面加载时先画出来查询位置点
    //后面画时候要注意把ctx.draw(true)参数写出true表示不覆盖上次绘图
    //创建mycanvas这个画布对象
    const ctx = wx.createCanvasContext("mycanvas");
    
    this.drawlocation(ctx)
    ctx.draw();

  },
  //在按钮点击事件画图  不知道为什么在真机上会有延迟 要按俩次button才绘出上次input传入的内容
  //解决方法放在forsubmit中画
  minDistance: function () {
    // console.log("minDistance")
    // //TODO:按照图创建邻接矩阵
    
    // var Graph=this.CreateMGraph();
    // console.log(Graph);
    // //TODO:Dijkstra算法解决单源最短路径问题（迪杰斯特拉）
    // console.log(this.Dijkstra(Graph,this.data.matrixStart,this.data.matrixDestination));
    // result = this.Dijkstra(Graph,this.data.matrixStart,this.data.matrixDestination);
    // //TODO:Floyd算法解决单源最短路径问题（佛洛依德）

    // //TODO:在界面中渲染出来最后结果 
    // this.DrawCanvas();
    // this.setData({
    //   isSearch: true
    // })
    // //将最后计算的结果存储到data中 
  },

  //canvas是在一个二维的网格当中 左上角坐标为（0，0）
  // width: 570rpx;
  // height: 980rpx;
  DrawCanvas: function () {
    //创建mycanvas这个画布对象
    const ctx = wx.createCanvasContext("mycanvas");
    
    this.drawPath(ctx,this.data.matrixStart,this.data.matrixDestination)
    this.drawtext(ctx,this.data.lookforwhat)
    // this.drawline(ctx);
    // ctx.draw()写在每个函数里面 就只能画出后一次的内容  因为后一次的内容会覆盖第一次的 
    //把后一次的ctx.draw()设置为ctx.draw(true)就表示不覆盖前一次的
    ctx.draw(true);
    
  },
  
  //在画布整体居中 固定位置画圆点 表示地方
  drawlocation: function (ctx) {
    
    //画圆
    function ball(x, y) {
      ctx.beginPath()
      ctx.arc(x, y, 5, 0, Math.PI * 2)
      ctx.setFillStyle('#4A148C')
      ctx.setStrokeStyle('#4A148C')
      ctx.closePath();
      ctx.fill()
      ctx.stroke()
    }
    
    for(var i=0;i<Coord.length;i++)
    {
      ball(Coord[i].x,Coord[i].y);
    }
    console.log("ball")
    // ctx.draw()
    
  },

  //画查询俩地之间的最短路径
  drawPath: function(ctx,start,destination) {
    // console.log(this.data.matrixDestination+"adadawdad")
    var i=destination;
    var temp = path[i];
    while(1){
      //能进入循环就是能执行
      ctx.beginPath()
      ctx.moveTo(Coord[i].x,Coord[i].y)
      ctx.lineTo(Coord[temp].x,Coord[temp].y)
      ctx.stroke()

      i=temp;
      temp = path[i];
      //循环退出条件  
      if(i===start) break;
    }
  },

  drawtext: function (ctx,index) {
    var x = 20;
    var y = 270;
    var text = this.data.start + "到" + this.data.destination + index+ "假装为：" + result;
    ctx.setFontSize(16)
    ctx.fillText(text, x, y)
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
      if(matrix[start][i]<Infinity)//路径初始化
      {
        path[i]=start; //源点到顶点i有边时，置顶点i的前一个顶点为源点
      }
      else{
        path[i]=-1; //没有边时，置顶点i的前一个顶点为-1
      }
      
    }
    dist[start]=0;
    s[start]=1; //源点编号start放入s中
    path[start]=0;
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
                  path[j]=u;
                }
            }
        } 
    }

    console.log(dist);
    console.log(path)
    //返回源点开始到每个顶点的最短路径数组
    // return dist;
    //返回从起点到终点的最短路径
    
    return dist[destination];
  },


  //选择函数 根据传值选择创建那种矩阵
  ChooseCreateGraph: function(index) {
    var Graph=[[]]
      switch (index) {
        case "dist":
          Graph = this.CreateMGraphDist();
          break;
        case "time":
          Graph = this.CreateMGraphTime();
          break;
        case "cost":
          Graph = this.CreateMGraphCost();
          break;
        case "custom":
          Graph = this.CreateMGraphDist();
          break;
      
        default:
          break;
      }
      return Graph;
  },
  // 三种不同查询寻求 创建三种不同的邻接矩阵
  //Distance
  CreateMGraphDist: function() {
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
  //Time
  CreateMGraphTime: function() {
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
  },
  //Cost
  CreateMGraphCost: function() {
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