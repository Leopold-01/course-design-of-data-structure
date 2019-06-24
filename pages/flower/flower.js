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
              title: '宁配🐎',
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