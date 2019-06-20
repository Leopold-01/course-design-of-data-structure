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

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {
    //当页面隐藏的时候把样式值修改为默认
    //这里设置会导致 动画结束后 到页面成功跳转 之间的间隙出现复位bug
    // this.setData({
    //   btn1:'',
    //   btn2:'',
    //   btn3:'',
    //   btn4:''
    // })
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