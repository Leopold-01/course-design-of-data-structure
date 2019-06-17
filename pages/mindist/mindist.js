Page({

  /**
   * 页面的初始数据
   */
  data: {
    btn1: '',
    btn2: '',
    btn3: '',
    btn4: '',
  },

  //动画完成后携带对应参数传到主页 查询
  Goindex: function (e) {
    console.log(e)
    return wx.navigateTo({
      url: '/pages/index/index',
      success: res =>{
        console.log("index")
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