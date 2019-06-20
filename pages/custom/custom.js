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