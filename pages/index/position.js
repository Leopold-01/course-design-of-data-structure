//用export暴露对象m
export const m = {}
//增加元素 这样增加可以模拟出Map的功能
//因为js的对象key值可以是自己定义 加''即可
m['合肥'] = 1
m['重庆'] = 2
m['武汉'] = 3
m['杭州'] = 4


//关于 exports和module.export
//首先要明确的一点，module是一个对象 {Object}。
//当每个js文件在执行或被require的时候，NodeJS其实创建了一个新的实例var module = new Module()，这个实例名叫module。
//这也就是为什么你并没有定义module这个变量，却能console.log出来而不会报错的原因。
// 由此也能看出，传说中的exports其实是module.exports的引用，
//你可以这么理解，NodeJS在你的代码之前悄悄的加了以下代码：

// var module = new Module();
// var exports = module.exports;

