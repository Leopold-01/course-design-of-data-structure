Page({

  /**
   * 页面的初始数据
   */
  data: {
    array: ['最短距离', '最低花费', '最短时间'],
    index: 0,
    isPicker: false,
    reminder: "这是一个可以点的东西",
    isShow:false,
    Up:true,
    start:'合肥',
    destination: '厦门'
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
    console.log('picker发送选择改变，携带值为', e.detail.value)
     this.setData({
         index: e.detail.value
     })
  },
  showList:function () {
    this.setData({
        isShow: true,
        Up:true
    })
  },
  down: function (){
    console.log("down")
    this.setData({
      
      Up:false
    })
  },
  back:function (){
    this.setData({
      isShow:false,
      
    })
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