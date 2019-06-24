var utils = require("../../utils/createMatrix")
const posS = require('./custom-data')

Page({

  /**
   * 页面的初始数据
   */
  data: {
    pos: posS.M,
    array: ['最短距离', '最低花费', '最短时间'],
    index: 0,
    isPicker: false,
    reminder: "点击选择你想要的查询方式",
    isShow:false,
    Up:true,
    start:'合肥',
    destination: '厦门',
    choose: '',
    unit:'',
    List:[]
  },
  backpage: function () {
    console.log("backkkkkkkkkkkk")
    wx.navigateBack({
      delta: 1
    })
  },
  chageToPicker:function (){
      //只在第一次点之前显示提示
    if(!this.data.isPicker)
    {
        this.setData({
            isPicker: true
        })
    }
  },
  bindPickerChange:function (e) {
    var that = this
    console.log('picker发送选择改变，携带值为', e.detail.value)
    //按照用户选择控制渲染出来内容
    switch (e.detail.value) {
      case "0":
        that.setData({
          choose: '距离',
          unit:'公里',
        })
        break;
      case "1":
        that.setData({
          choose: '费用',
          unit:'元',
        })
        break;
      case "2":
        that.setData({
          choose: '时间',
          unit:'小时',
        })
        break;
    
      default:
        break;
    }
    console.log(this.data.choose)
     this.setData({
         index: e.detail.value
     })
  },
  // *************主要函数
  showList:function () {
    this.setData({
        isShow: true,
        Up:true
    })
  
    //创建用户选择的邻接矩阵
    var Graph=utils.ChooseCreateGraph(this.data.index)
    var A = this.Floyd(Graph)
    console.log(A)
    //将邻接矩阵排序存到List中 便于后续遍历输出
    //俩层函数调用 第二层直接用this点不出来
    this.TrunToList(A,this)
    
  },
  down: function (){
    console.log("down")
    this.setData({
      Up:false
    })
    console.log(this.data.List)
  },
  back:function (){
    this.setData({
      isShow:false,
      
    })
  },


  //把二维数组A中存的每个顶点间的最短路径放到一个排好序的对象数组中 
  //这样在渲染的时候可以渲染出具体顶点名称（A的下标）和value
  TrunToList: function(A,that){
    // var objectTpl = {
    //   x: 0,
    //   y: 0,
    //   value: Infinity
    // }
    var List=[]
    var name=that.data.pos;
    console.log(name)
    console.log(A.length)
    //遍历A数组 先存到List中
    for(var i = 0;i<A.length;i++)
    {
      for(var j =0 ; j<A.length;j++)
      {
        
        if(i===j)break;//因为是无向图 所以控制只用录入矩阵下三角
        // 作用域问题 每次引用objecTpl在js里地址是不会改变的
        //所以每次调用地址一样，值就会覆盖数组前面的赋值
        //因为数组前面存储的都是地址（现在地址不变 所以存的都是同一个地址）
        //解决：在循环时 每次引用都重新声明
        var objectTpl = {
          start: '',
          destination: '',
          value: Infinity
        }
        var temp = new Object(objectTpl)
        temp.start=name[i];
        temp.destination=name[j];
        temp.value=A[i][j];
        List.push(temp)
        // console.log(temp)
        //忘记index++了 不需要 用arr.push(obj)就好了
        
      }
    }
    // console.log(temp)
    // console.log(List)
    //js sort 先写排序函数
    function compare(propertyName) {
      return function(object1,object2) {
        var value1= object1[propertyName];
        var value2= object2[propertyName];
        // if(value2 > value1)
        // {
        //   return 1;
        // }else if(value2 < value1)
        // {
        //   return -1;
        // }else{
        //   return 0;
        // }
        //上面代码可以写成
        return value1-value2;
      }
    }
    List.sort(compare('value'))
    //log结果显示 这里List在排序前后写的都是一样的被排序了。
    //知道时js作用域问题（地址一样？） 但还是不太理解
    console.log(List)
    that.setData({
      List:List
    })
  },



  //Floyd（弗洛伊德）算法 把所有顶点间最短距离存储在二维数组内
  Floyd: g=>{
    var length= g.length
    var i,j,k;
    // 二维数组存储矩阵间的最短路径
    var A = new Array(length)
    for(var aa=0;aa<length;aa++)
    {
      A[aa]=new Array(length)
    }
    //初始化最短路径二维数组A
    for(i=0;i<length;i++)
      for(j=0;j<length;j++)
        {
          A[i][j] = g[i][j];
        }
    //每个顶点都有可能使得另外俩个顶点间路程变短
    
    //即A[i][j]>A[i][k]+A[k][j] i到j的距离如果小于加上中转点 则更新距离
    //详见博客https://www.cnblogs.com/wangyuliang/p/9216365.html
    for(k=0;k<length;k++)
    {
      for(i=0;i<length;i++)
        {
          for(j=0;j<length;j++)
            {
              if(A[i][j]>A[i][k]+A[k][j])
                {
                  A[i][j]=A[i][k]+A[k][j];
                }
            }
        }
    }
    return A;
  },
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    

    console.log(utils)
    console.log(this.data.pos)
    
  },
  
  
})











Page({

  /**
   * 页面的初始数据
   */
  data: {
    enter:''
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function() {
    
},

  LoginEnter: function(e) {
      // 查看是否授权wx.getSetting返回已经向用户请求过的权限
      //res内容如下
      // res.authSetting = {
      //   "scope.userInfo": true,
      //   "scope.userLocation": true
      // }
      //授权有效期
      //一旦用户明确同意或拒绝过授权，其授权关系会记录在后台，直到用户主动删除小程序。
      wx.getSetting({
          success: function(res) {
              if (res.authSetting['scope.userInfo']) {
                  wx.getUserInfo({
                      success: function(res) {
                          // 用户已经授权过,不需要显示授权页面,所以不需要改变 isHide 的值
                          // 根据自己的需求有其他操作再补充
                          // 我这里实现的是在用户授权成功后，调用微信的 wx.login 接口，从而获取code
                          wx.login({
                              success: res => {
                                  // 获取到用户的 code 之后：res.code
                                  console.log("用户的code:" + res.code);
                                  // 可以传给后台，再经过解析获取用户的 openid
                                  // 或者可以直接使用微信的提供的接口直接获取 openid ，方法如下：
                                   wx.request({
                                      // 自行补上自己的 APPID 和 SECRET
                                       url: 'https://api.weixin.qq.com/sns/jscode2session?appid=wx8a682217d2a74bc3&secret=ecc0683bb96f19feef458f24a1f80988&js_code=' + res.code + '&grant_type=authorization_code',
                                      success: res => {
                                          // 获取到用户的 openid
                                          // unionid获取现在是unefined 详见unionid机制说明
                                          console.log("后台解析后用户信息:"+res.data.session_key)
                                          console.log("用户的openid:" + res.data.openid);
                                      }
                                  });
                              }
                          });
                      }
                  });
                  return wx.navigateTo({
                    url: '/pages/mindist/mindist',
                    success: res =>{
                      console.log("11111111")
                    }
                  })
              } 
              
          }
      });
      if (e.detail.userInfo) {
          //用户按了允许授权按钮
          // 获取到用户的信息了，打印到控制台上看下
          console.log("用户的信息如下：");
          console.log(e.detail.userInfo);
          //授权成功后,通过改变 isHide 的值，让实现页面显示出来，把授权页面隐藏起来
          
      } else {
          //用户按了拒绝按钮
          wx.showModal({
              title: '宁配??',
              content: '您点击了拒绝授权，不过也没事，你还能进来：）',
              showCancel: false,
              confirmText: 'Rush B',
              success: function(res) {
                  // 用户没有授权成功，不需要改变 isHide 的值
                  if (res.confirm) {
                      console.log('用户点击了“返回授权”');
                      return wx.navigateTo({
                        url: '/pages/mindist/mindist',
                        success: res =>{
                          console.log("333333")
                        }
                      })
                  }
              }
          });
      }
  },


  
 
})













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
    //当输入地名不存在时弹出toast
    
    if((num[start1]>=0&&num[start1]<=6)&&(num[destination1]>=0&&num[destination1]<=6))
    {
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
    }else{
      wx.showModal({
        title: '提示',
        content: '因为懒得模拟太多数据所以地名仅支持：合肥、重庆、武汉、杭州、成都、上海、厦门',
        success (res) {
          if (res.confirm) {
            console.log('用户点击确定')
          } else if (res.cancel) {
            console.log('用户点击取消')
          }
        }
      })
      
    }
    
    
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
  backpage:function () {
    console.log("backkkkkkkkkkkk")
    wx.navigateBack({
      delta: 1
    })
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
    this.drawlocation(ctx)
    this.drawPath(ctx,this.data.matrixStart,this.data.matrixDestination)
    this.drawtext(ctx,this.data.lookforwhat)
    // this.drawline(ctx);
    // ctx.draw()写在每个函数里面 就只能画出后一次的内容  因为后一次的内容会覆盖第一次的 
    //把后一次的ctx.draw()设置为ctx.draw(true)就表示不覆盖前一次的
    ctx.draw(false);
    
  },
  
  //在画布整体居中 固定位置画圆点 表示地方
  drawlocation: function (ctx) {
    
    //画圆
    function ball(x, y) {
      ctx.beginPath()
      ctx.arc(x, y, 5, 0, Math.PI * 2)
      ctx.setFillStyle('#27d7cd')
      ctx.setStrokeStyle('#27d7cd')
      ctx.closePath();
      ctx.fill()
      ctx.stroke()
    }
    
    for(var i=0;i<Coord.length;i++)
    {
      ball(Coord[i].x,Coord[i].y);
      //写上城市名字
      ctx.setFontSize(16)
      var text= posS.M[i]
      ctx.fillText(text, Coord[i].x-13, Coord[i].y-12)
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
  //index为dist/cost/time
  drawtext: function (ctx,index) {
    var x = Coord[4].x-50;
    var y = Coord[5].y+50;
    var desc='';
    var unit='';
    switch (index) {
      case 'time':
        desc='需要最短时间为：'
        unit='小时'
        break;
      case 'cost':
        desc='需要最少费用为：'
        unit='元'
        break;
      case 'dist':
        desc='最短路径为：'
        unit='公里'
        break;
    
      default:
        break;
    }
    var text = this.data.start + "到" + this.data.destination + desc+ result+unit;
    ctx.setFontSize(17)
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
})




Page({

  /**
   * 页面的初始数据
   */
  data: {
    btn1: '',
    btn2: '',
    btn3: '',
    btn4: '',
    index: ''
  },
  
  backpage: function () {
    console.log("backkkkkkkkkkkk")
    wx.navigateBack({
      delta: 1
    })
  },
  //动画完成后携带对应参数传到主页 查询
  //bindanimationend好像在页面有多个动画同时播放时 无法判断是点击的哪个
  //我可以通过用来控制动画的值来判断跳转页面要传的对应值
  Goindex: function (e) {
    
    var url='';
    console.log(e)
    switch (this.data.index) {
      case "dist":
        url= '/pages/index/index?id=dist'
        break;
      case "cost":
        url= '/pages/index/index?id=cost'
        break;
      case "time":
        url= '/pages/index/index?id=time'
        break;
      case "custom":
        url= '/pages/custom/custom'
        break;
    
      default:
        break;
    }
    // wx.navigateTo  url的pages只能写单引号
    return wx.navigateTo({
      url: url,
      //回调函数
      success: res =>{
        console.log("跳转成功")
      }
    })
  },

  //按钮播放动画
  JumpToDist: function (e) {
    console.log(e)
    this.setData({
      btn1: e.currentTarget.dataset.btn1,
      btn2: e.currentTarget.dataset.btn2,
      btn3: e.currentTarget.dataset.btn3,
      btn4: e.currentTarget.dataset.btn4,
      index: e.currentTarget.dataset.btn1
    })
    console.log(this.data.btn1)
    
  },
  JumpToCost: function (e) {
    console.log(e)
    this.setData({
      btn1: e.currentTarget.dataset.btn1,
      btn2: e.currentTarget.dataset.btn2,
      btn3: e.currentTarget.dataset.btn3,
      btn4: e.currentTarget.dataset.btn4,
      index: e.currentTarget.dataset.btn2
    })
    console.log(this.data.btn2)
  },
  JumpToTime: function (e) {
    console.log(e)
    this.setData({
      btn1: e.currentTarget.dataset.btn1,
      btn2: e.currentTarget.dataset.btn2,
      btn3: e.currentTarget.dataset.btn3,
      btn4: e.currentTarget.dataset.btn4,
      index: e.currentTarget.dataset.btn3
    })
    console.log(this.data.btn3)
  },
  JumpToCustom: function (e) {
    console.log(e)
    this.setData({
      btn1: e.currentTarget.dataset.btn1,
      btn2: e.currentTarget.dataset.btn2,
      btn3: e.currentTarget.dataset.btn3,
      btn4: e.currentTarget.dataset.btn4,
      index: e.currentTarget.dataset.btn4
    })
    console.log(this.data.btn4)
  },
  
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    
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
    //当页面在显示的时候把样式值修改为默认
    this.setData({
      btn1:'',
      btn2:'',
      btn3:'',
      btn4:''
    })
  },

 
})
