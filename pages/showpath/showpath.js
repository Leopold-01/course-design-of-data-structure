
Page({

  /**
   * 页面的初始数据
   */
  data: {
    isShow:false,
    imageW: "",
    imageH: ""

  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    //创建mycanvas这个画布对象
    const ctx = wx.createCanvasContext("mycanvas");
    const canvasWidth = 375;
    const canvasHeight = 667;
    // this.drawlocation(ctx,canvasWidth,canvasHeight);
    // this.drawline(ctx);
    // ctx.draw()写在每个函数里面 就只能画出后一次的内容  因为后一次的内容会覆盖第一次的 
    //把后一次的ctx.draw()设置为ctx.draw(true)就表示不覆盖前一次的
    // 为什么这里要把this先赋值给that呢 
    //好像是因为this指向同级 that这里是再onload下面的一级
    var that = this
    wx.getSystemInfo({
      
      success: function(res) {
        //设置image宽高为屏幕宽高
        that.setData({
          imageW: res.windowWidth,
          imageH: res.windowHeight,
        })

      }
    })
    var img = "../../static/images/map.png"
    ctx.drawImage(img, 0, 0 , this.data.imageW, this.data.imageH)
    ctx.draw();
  },
  draw: function () {
    
    
    
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

  //在画布整体居中 固定位置画圆点 表示地方
  drawlocation: function (ctx,Width,Height) {
    const canvasCenterX = Width/2;
    const canvasCenterY = Height/2;
    //画圆
    function ball(x, y) {
      ctx.beginPath()
      ctx.arc(x, y, 5, 0, Math.PI * 2)
      ctx.setFillStyle('#1aad19')
      ctx.setStrokeStyle('#2980b9')
      ctx.closePath();
      ctx.fill()
      ctx.stroke()
    }
    for(var i =0;i<7;i++)
    {
      ball(canvasCenterX, canvasCenterY-100+i*10)
    }
    // ctx.translate(canvasCenterX, canvasCenterY);
    // ctx.rotate(20 * Math.PI / 180)
    // ctx.draw()
    
  },

  //画俩点间连线 先测试
  // drawline: function (ctx) {
  //     var x= 375/2-50;
  //     var y= 500/2+50;
  //     var xx= x -100;
  //     var yy= y +100;
  //     ctx.beginPath()
  //     ctx.moveTo(x, y)
  //     ctx.lineTo(xx, yy)
  //     ctx.stroke()
  //     ctx.closePath();
  //     //true表示不覆盖前一次绘制
  //     // ctx.draw(true)
  // },
  
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