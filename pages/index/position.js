//用export暴露对象m
export const m = {}
//增加元素 这样增加可以模拟出Map的功能
//因为js的对象key值可以是自己定义 加''即可
m['合肥'] = 0
m['重庆'] = 1
m['武汉'] = 2
m['杭州'] = 3
m['成都'] = 4
m['厦门'] = 5
m['上海'] = 6

export const M = {}
M[0]='合肥'
M[1]='重庆'
M[2]='武汉'
M[3]='杭州'
M[4]='成都'
M[5]='厦门'
M[6]='上海'

const canvasCenterX = 182;
const canvasCenterY = 170;
const gap= 100;
const gap1 =15;
//七个点的坐标
export const Coord = [
  {
    x: canvasCenterX,
    y: canvasCenterY - gap-10
  },
  {
    x: canvasCenterX -gap +gap1,
    y: canvasCenterY -gap/2
  },
  {
    x: canvasCenterX,
    y: canvasCenterY 
  },
  {
    x: canvasCenterX + gap -gap1,
    y: canvasCenterY -gap/2
  },
  {
    x: canvasCenterX -gap +gap1,
    y: canvasCenterY + gap -gap/2
  },
  {
    x: canvasCenterX,
    y: canvasCenterY + gap
  },
  {
    x: canvasCenterX +gap-gap1,
    y: canvasCenterY + gap -gap/2
  }
]

//关于 exports和module.export
//首先要明确的一点，module是一个对象 {Object}。
//当每个js文件在执行或被require的时候，NodeJS其实创建了一个新的实例var module = new Module()，这个实例名叫module。
//这也就是为什么你并没有定义module这个变量，却能console.log出来而不会报错的原因。
// 由此也能看出，传说中的exports其实是module.exports的引用，
//你可以这么理解，NodeJS在你的代码之前悄悄的加了以下代码：

// var module = new Module();
// var exports = module.exports;

