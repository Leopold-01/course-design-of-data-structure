var utils = require("../../utils/createMatrix")
const posS = require('./custom-data')

Page({

  /**
   * ҳ��ĳ�ʼ����
   */
  data: {
    pos: posS.M,
    array: ['��̾���', '��ͻ���', '���ʱ��'],
    index: 0,
    isPicker: false,
    reminder: "���ѡ������Ҫ�Ĳ�ѯ��ʽ",
    isShow:false,
    Up:true,
    start:'�Ϸ�',
    destination: '����',
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
      //ֻ�ڵ�һ�ε�֮ǰ��ʾ��ʾ
    if(!this.data.isPicker)
    {
        this.setData({
            isPicker: true
        })
    }
  },
  bindPickerChange:function (e) {
    var that = this
    console.log('picker����ѡ��ı䣬Я��ֵΪ', e.detail.value)
    //�����û�ѡ�������Ⱦ��������
    switch (e.detail.value) {
      case "0":
        that.setData({
          choose: '����',
          unit:'����',
        })
        break;
      case "1":
        that.setData({
          choose: '����',
          unit:'Ԫ',
        })
        break;
      case "2":
        that.setData({
          choose: 'ʱ��',
          unit:'Сʱ',
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
  // *************��Ҫ����
  showList:function () {
    this.setData({
        isShow: true,
        Up:true
    })
  
    //�����û�ѡ����ڽӾ���
    var Graph=utils.ChooseCreateGraph(this.data.index)
    var A = this.Floyd(Graph)
    console.log(A)
    //���ڽӾ�������浽List�� ���ں����������
    //���㺯������ �ڶ���ֱ����this�㲻����
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


  //�Ѷ�ά����A�д��ÿ�����������·���ŵ�һ���ź���Ķ��������� 
  //��������Ⱦ��ʱ�������Ⱦ�����嶥�����ƣ�A���±꣩��value
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
    //����A���� �ȴ浽List��
    for(var i = 0;i<A.length;i++)
    {
      for(var j =0 ; j<A.length;j++)
      {
        
        if(i===j)break;//��Ϊ������ͼ ���Կ���ֻ��¼�����������
        // ���������� ÿ������objecTpl��js���ַ�ǲ���ı��
        //����ÿ�ε��õ�ַһ����ֵ�ͻḲ������ǰ��ĸ�ֵ
        //��Ϊ����ǰ��洢�Ķ��ǵ�ַ�����ڵ�ַ���� ���Դ�Ķ���ͬһ����ַ��
        //�������ѭ��ʱ ÿ�����ö���������
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
        //����index++�� ����Ҫ ��arr.push(obj)�ͺ���
        
      }
    }
    // console.log(temp)
    // console.log(List)
    //js sort ��д������
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
        //����������д��
        return value1-value2;
      }
    }
    List.sort(compare('value'))
    //log�����ʾ ����List������ǰ��д�Ķ���һ���ı������ˡ�
    //֪��ʱjs���������⣨��ַһ������ �����ǲ�̫���
    console.log(List)
    that.setData({
      List:List
    })
  },



  //Floyd���������£��㷨 �����ж������̾���洢�ڶ�ά������
  Floyd: g=>{
    var length= g.length
    var i,j,k;
    // ��ά����洢���������·��
    var A = new Array(length)
    for(var aa=0;aa<length;aa++)
    {
      A[aa]=new Array(length)
    }
    //��ʼ�����·����ά����A
    for(i=0;i<length;i++)
      for(j=0;j<length;j++)
        {
          A[i][j] = g[i][j];
        }
    //ÿ�����㶼�п���ʹ���������������·�̱��
    
    //��A[i][j]>A[i][k]+A[k][j] i��j�ľ������С�ڼ�����ת�� ����¾���
    //�������https://www.cnblogs.com/wangyuliang/p/9216365.html
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
   * �������ں���--����ҳ�����
   */
  onLoad: function (options) {
    

    console.log(utils)
    console.log(this.data.pos)
    
  },
  
  
})











Page({

  /**
   * ҳ��ĳ�ʼ����
   */
  data: {
    enter:''
  },

  /**
   * �������ں���--����ҳ�����
   */
  onLoad: function() {
    
},

  LoginEnter: function(e) {
      // �鿴�Ƿ���Ȩwx.getSetting�����Ѿ����û��������Ȩ��
      //res��������
      // res.authSetting = {
      //   "scope.userInfo": true,
      //   "scope.userLocation": true
      // }
      //��Ȩ��Ч��
      //һ���û���ȷͬ���ܾ�����Ȩ������Ȩ��ϵ���¼�ں�̨��ֱ���û�����ɾ��С����
      wx.getSetting({
          success: function(res) {
              if (res.authSetting['scope.userInfo']) {
                  wx.getUserInfo({
                      success: function(res) {
                          // �û��Ѿ���Ȩ��,����Ҫ��ʾ��Ȩҳ��,���Բ���Ҫ�ı� isHide ��ֵ
                          // �����Լ������������������ٲ���
                          // ������ʵ�ֵ������û���Ȩ�ɹ��󣬵���΢�ŵ� wx.login �ӿڣ��Ӷ���ȡcode
                          wx.login({
                              success: res => {
                                  // ��ȡ���û��� code ֮��res.code
                                  console.log("�û���code:" + res.code);
                                  // ���Դ�����̨���پ���������ȡ�û��� openid
                                  // ���߿���ֱ��ʹ��΢�ŵ��ṩ�Ľӿ�ֱ�ӻ�ȡ openid ���������£�
                                   wx.request({
                                      // ���в����Լ��� APPID �� SECRET
                                       url: 'https://api.weixin.qq.com/sns/jscode2session?appid=wx8a682217d2a74bc3&secret=ecc0683bb96f19feef458f24a1f80988&js_code=' + res.code + '&grant_type=authorization_code',
                                      success: res => {
                                          // ��ȡ���û��� openid
                                          // unionid��ȡ������unefined ���unionid����˵��
                                          console.log("��̨�������û���Ϣ:"+res.data.session_key)
                                          console.log("�û���openid:" + res.data.openid);
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
          //�û�����������Ȩ��ť
          // ��ȡ���û�����Ϣ�ˣ���ӡ������̨�Ͽ���
          console.log("�û�����Ϣ���£�");
          console.log(e.detail.userInfo);
          //��Ȩ�ɹ���,ͨ���ı� isHide ��ֵ����ʵ��ҳ����ʾ����������Ȩҳ����������
          
      } else {
          //�û����˾ܾ���ť
          wx.showModal({
              title: '����??',
              content: '������˾ܾ���Ȩ������Ҳû�£��㻹�ܽ�������',
              showCancel: false,
              confirmText: 'Rush B',
              success: function(res) {
                  // �û�û����Ȩ�ɹ�������Ҫ�ı� isHide ��ֵ
                  if (res.confirm) {
                      console.log('�û�����ˡ�������Ȩ��');
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













//TODO���û������ѯ�� �Ȼ�ȡǰ���û�����ĵ��� 
//������ת��Ϊ�����е�����(��js�Ķ���ģ���ֵ䣨��ֵ�ԣ��Ĵ洢�ṹ)
//Map��ֵ�Դ洢���Է���Ľ�����ת��Ϊ��Ӧ�±�
//΢��С������ʹ��Map�޷���get set������ȡ���� �����Լ�ģ��һ��

//������ô��Ҳֻ�Ƿ����˶�ȡ�������ֶ�Ӧ���±�ʱ���ñ��������ȡ����  
//����ʹ���л���Ҫ������������Ȼ�������  ��Ϊ��ֵ��Ӧ�����ݲ���һ���±� ����canvas�е�λ������
//��������������һ�������������洢 ���е�canvas����
//д��position�ļ��� ��������
const coord = require('./position')
const Coord =coord.Coord;
//require������nodejs������û�п������õ�
const posS = require('./position.js')
//����ʹ��ģ�黯��������в��� ������
// const Graph = require("../../utils/CreateMGraph")
//��Ϊȫ�ֲ������ش�ֵ
//path����Դ��v��ͼ������������·�� path[i]��ʾv->j�����·����j��Ӧ����һ����
var path = new Array(10000);
var result = '';
Page({
  /**
   * ҳ��ĳ�ʼ����
   */
  
  data: {
    //��ȡ��������Ӧ���ڽӾ����±�
    pos: posS.m,
    //��ȡ�û�����ĵ���
    start: '',
    destination: '',
    //Ҫ����ʼֵ
    matrixStart: 0,
    matrixDestination: 0,
    //��ʼ��ͼ���ڽӾ���
    mGraph: [[]],
    isSearch: false,
    imageW: "",
    imageH: "",
    //��¼��ǰҳ��Ҫ��ѯ������
    lookforwhat: "",
  },

  //�õ�ҳ���û������Ŀ�ĵ�
  formSubmit: function (e) {
    console.log('form������submit�¼���Я������Ϊ��', e);
    //����Ĵ���������Ҫ�ȴ洢һ�� ����setData�и�ֵ ��Ȼ����
    //Cannot read property 'value' of undefined;
    const start1 = e.detail.value.start_input;
    const destination1 = e.detail.value.destination_input;
    this.setData({
      start: start1,
      destination: destination1
    })
    //���Գɹ����û�����ĵ����洢
    // console.log(this.data.start)
    const num = this.data.pos;
    //��Ϊ��һ��input����� ��ڶ�input��֪��Ϊʲô��ֱ���ύ���� ��������ڶ���ֵ��ֵ�ᱨ�� �����ж����ٸ�ֵ
    //���������������ʱ����toast
    
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
          //TODO:����ͼ�����ڽӾ���
          
          var Graph = this.ChooseCreateGraph(this.data.lookforwhat);
          console.log(Graph);
          //TODO:Dijkstra�㷨�����Դ���·�����⣨�Ͻ�˹������
          console.log(this.Dijkstra(Graph, this.data.matrixStart, this.data.matrixDestination));
          result = this.Dijkstra(Graph, this.data.matrixStart, this.data.matrixDestination);
          //TODO:Floyd�㷨�����Դ���·�����⣨�������£�
      
          //TODO:�ڽ�������Ⱦ��������� 
          this.DrawCanvas();
          this.setData({
            isSearch: true
          })
          //��������Ľ���洢��data�� 
    }else{
      wx.showModal({
        title: '��ʾ',
        content: '��Ϊ����ģ��̫���������Ե�����֧�֣��Ϸʡ����졢�人�����ݡ��ɶ����Ϻ�������',
        success (res) {
          if (res.confirm) {
            console.log('�û����ȷ��')
          } else if (res.cancel) {
            console.log('�û����ȡ��')
          }
        }
      })
      
    }
    
    
  },
  /**
   * �������ں���--����ҳ�����
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
    //��ҳ�����ʱ�Ȼ�������ѯλ�õ�
    //���滭ʱ��Ҫע���ctx.draw(true)����д��true��ʾ�������ϴλ�ͼ
    //����mycanvas�����������
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
  //�ڰ�ť����¼���ͼ  ��֪��Ϊʲô������ϻ����ӳ� Ҫ������button�Ż���ϴ�input���������
  //�����������forsubmit�л�
  minDistance: function () {
    // console.log("minDistance")
    // //TODO:����ͼ�����ڽӾ���
    
    // var Graph=this.CreateMGraph();
    // console.log(Graph);
    // //TODO:Dijkstra�㷨�����Դ���·�����⣨�Ͻ�˹������
    // console.log(this.Dijkstra(Graph,this.data.matrixStart,this.data.matrixDestination));
    // result = this.Dijkstra(Graph,this.data.matrixStart,this.data.matrixDestination);
    // //TODO:Floyd�㷨�����Դ���·�����⣨�������£�

    // //TODO:�ڽ�������Ⱦ��������� 
    // this.DrawCanvas();
    // this.setData({
    //   isSearch: true
    // })
    // //��������Ľ���洢��data�� 
  },

  //canvas����һ����ά�������� ���Ͻ�����Ϊ��0��0��
  // width: 570rpx;
  // height: 980rpx;
  DrawCanvas: function () {
    //����mycanvas�����������
    const ctx = wx.createCanvasContext("mycanvas");
    this.drawlocation(ctx)
    this.drawPath(ctx,this.data.matrixStart,this.data.matrixDestination)
    this.drawtext(ctx,this.data.lookforwhat)
    // this.drawline(ctx);
    // ctx.draw()д��ÿ���������� ��ֻ�ܻ�����һ�ε�����  ��Ϊ��һ�ε����ݻḲ�ǵ�һ�ε� 
    //�Ѻ�һ�ε�ctx.draw()����Ϊctx.draw(true)�ͱ�ʾ������ǰһ�ε�
    ctx.draw(false);
    
  },
  
  //�ڻ���������� �̶�λ�û�Բ�� ��ʾ�ط�
  drawlocation: function (ctx) {
    
    //��Բ
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
      //д�ϳ�������
      ctx.setFontSize(16)
      var text= posS.M[i]
      ctx.fillText(text, Coord[i].x-13, Coord[i].y-12)
    }
    console.log("ball")
    // ctx.draw()
    
  },

  //����ѯ����֮������·��
  drawPath: function(ctx,start,destination) {
    // console.log(this.data.matrixDestination+"adadawdad")
    var i=destination;
    var temp = path[i];
    while(1){
      //�ܽ���ѭ��������ִ��
      ctx.beginPath()
      ctx.moveTo(Coord[i].x,Coord[i].y)
      ctx.lineTo(Coord[temp].x,Coord[temp].y)
      ctx.stroke()

      i=temp;
      temp = path[i];
      //ѭ���˳�����  
      if(i===start) break;
    }
  },
  //indexΪdist/cost/time
  drawtext: function (ctx,index) {
    var x = Coord[4].x-50;
    var y = Coord[5].y+50;
    var desc='';
    var unit='';
    switch (index) {
      case 'time':
        desc='��Ҫ���ʱ��Ϊ��'
        unit='Сʱ'
        break;
      case 'cost':
        desc='��Ҫ���ٷ���Ϊ��'
        unit='Ԫ'
        break;
      case 'dist':
        desc='���·��Ϊ��'
        unit='����'
        break;
    
      default:
        break;
    }
    var text = this.data.start + "��" + this.data.destination + desc+ result+unit;
    ctx.setFontSize(17)
    ctx.fillText(text, x, y)
  },

  
  //distance�д洢����Ŀǰ��Դ�㵽ÿ������ļ����·��
  Dijkstra: function(matrix, start ,destination) {
    const rows = matrix.length,//rows��colsһ������ʵ���Ƕ������
        cols = matrix[0].length;
    var s = new Array(10000);
    var dist = new Array(10000);
    
    // var path = new Array(10000);������ʱ����Ҫpath
    var mindis,i,j,u;
    if(rows !== cols || start >= rows) return new Error("�ڽӾ���������Դ�����");

    //��ʼ��
    for(i=0;i<rows;i++)
    {
      //�洢Դ�㵽���ж����Ŀǰ���·������ ���Գ�ʼʱ����ΪԴ����һ�о����ֵ
      dist[i]=matrix[start][i];//�����ʼ��
      s[i]=0;//s[]�ÿ�
      if(matrix[start][i]<Infinity)//·����ʼ��
      {
        path[i]=start; //Դ�㵽����i�б�ʱ���ö���i��ǰһ������ΪԴ��
      }
      else{
        path[i]=-1; //û�б�ʱ���ö���i��ǰһ������Ϊ-1
      }
      
    }
    dist[start]=0;
    s[start]=1; //Դ����start����s��
    path[start]=0;
    for(i=0;i<rows;i++) //ѭ��ֱ�������ж�������·�������
    {
        mindis=Infinity;//mindis����С���ȳ�ֵ
        for(j=0;j<cols;j++)//ѡȡ����s���Ҿ�����С����Ķ���u
        {
          if(s[j]===0 && dist[j]<mindis)
            {
              u=j;
              mindis=dist[j];
            }
        }
        //�ҵ���С��u
        s[u]=1; //����u����s��
        for(j=0;j<cols;j++)//�޸Ĳ���s�еĶ���ľ���
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
    //����Դ�㿪ʼ��ÿ����������·������
    // return dist;
    //���ش���㵽�յ�����·��
    
    return dist[destination];
  },


  //ѡ���� ���ݴ�ֵѡ�񴴽����־���
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
  // ���ֲ�ͬ��ѯѰ�� �������ֲ�ͬ���ڽӾ���
  //Distance
  CreateMGraphDist: function() {
    //js���ö����������� ���������� ����������ֵ�����;�����ʲô���͵�����
    var i,j;
    var n=7;//ͼ�Ķ�����
    //js�Ķ�ά�����ʼ��
    var MGraph = new Array(n);//nΪ���������� ��ͼ�Ķ������
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
    //js���ö����������� ���������� ����������ֵ�����;�����ʲô���͵�����
    var i,j;
    var n=7;//ͼ�Ķ�����
    //js�Ķ�ά�����ʼ��
    var MGraph = new Array(n);//nΪ���������� ��ͼ�Ķ������
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
    //js���ö����������� ���������� ����������ֵ�����;�����ʲô���͵�����
    var i,j;
    var n=7;//ͼ�Ķ�����
    //js�Ķ�ά�����ʼ��
    var MGraph = new Array(n);//nΪ���������� ��ͼ�Ķ������
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
   * ҳ��ĳ�ʼ����
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
  //������ɺ�Я����Ӧ����������ҳ ��ѯ
  //bindanimationend������ҳ���ж������ͬʱ����ʱ �޷��ж��ǵ�����ĸ�
  //�ҿ���ͨ���������ƶ�����ֵ���ж���תҳ��Ҫ���Ķ�Ӧֵ
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
    // wx.navigateTo  url��pagesֻ��д������
    return wx.navigateTo({
      url: url,
      //�ص�����
      success: res =>{
        console.log("��ת�ɹ�")
      }
    })
  },

  //��ť���Ŷ���
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
   * �������ں���--����ҳ�����
   */
  onLoad: function (options) {
    
  },

  /**
   * �������ں���--����ҳ�������Ⱦ���
   */
  onReady: function () {
    
  },

  /**
   * �������ں���--����ҳ����ʾ
   */
  onShow: function () {
    //��ҳ������ʾ��ʱ�����ʽֵ�޸�ΪĬ��
    this.setData({
      btn1:'',
      btn2:'',
      btn3:'',
      btn4:''
    })
  },

 
})
