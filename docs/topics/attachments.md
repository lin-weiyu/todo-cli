# 附件：元数据 + 文件字节的分层设计

> 对应实现：[IAttachmentStorage.h](../../include/storage/IAttachmentStorage.h)、
> [SQLiteAttachmentStorage](../../src/storage/SQLiteAttachmentStorage.cpp)、
> [Attachment.h](../../include/core/Attachment.h)。这是 P1「每任务多文档附件」的架构笔记。

## 一个附件需要存两样东西

- **元数据**：附件叫什么、属于哪个任务、id 多少 → 放 SQLite 的 `attachments` 表。
- **文件字节**：文件内容本身 → 放受管理的 `data/attachments/` 目录。

两者必须分开：SQLite 擅长管「关系 / 查询」，不擅长管大文件；文件放文件系统，
数据库只存「指向它的线索」（id + 原始文件名）。

## id 是「两个世界」之间的桥

物理文件名 = 附件 id：

```text
attachments 表：  id=3, task_id=1, original_name="报告.pdf"
文件系统：        data/attachments/3   ← 文件内容在这
```

`id` 由 SQLite 生成（`last_insert_rowid`），文件用这个 id 命名；`original_name`
存起来用于「取回时还原成 报告.pdf」。

## 两种正交的分层（容易混）

| 分层 | 是什么 | 例子 |
|------|--------|------|
| A. 业务 vs 持久化 | 谁做决策 vs 谁读写数据 | TodoManager vs Storage |
| B. 元数据 vs 文件字节 | 存关系 vs 存字节 | SQLite 表 vs 文件系统 |

这两个分层互相独立。附件的完整结构：

```text
CLI → AttachmentManager（业务编排，不缓存）
         ├─► IAttachmentStorage（元数据：add/list/get/remove，SQLite）
         └─► 文件存储（字节：store/getPath/remove，文件系统）
```

## 为什么「查列表」是存储层的事，不是 Manager 的事

关键区别：`TodoManager` 在内存里缓存了 `vector<Todo>`，所以 `listTodos()` 只是
打印内存数据、不碰存储；而附件采用**按操作、不缓存**，所以「查某任务的附件」
本身就是一次 `SELECT`，必须落在存储层。

> 一句话：一旦不在内存缓存数据，「查询」本身就成了存储层的事，Manager 变薄、只做编排。

## 跨层一致性（失败回滚）

`attach` 的完整流程是三步，且 SQLite 事务只保护元数据那一半：

```text
1. INSERT 元数据 → 拿到 id
2. 复制文件 → data/attachments/<id>
3. 第 2 步失败 → 回头删掉第 1 步的元数据（回滚）
```

文件操作成功而数据库失败、或相反，只能靠代码手动清理——数据库事务保护不了
文件系统那一半。

## 命名注意

`SQLiteAttachmentStorage` 里的 "Storage" 是「持久化抽象」的意思（和 `IStorage`、
`SQLiteStorage` 平行），**不是**「文件存储」。更精确可叫 `SQLiteAttachmentRepository`，
本项目为与 `SQLiteStorage` 平行而沿用 `...Storage`。
