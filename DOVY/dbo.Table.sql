CREATE TABLE [dbo].[Table]
(
	[Id] INT NOT NULL PRIMARY KEY, 
    [UserName] VARCHAR(50) NOT NULL, 
    [Password] VARCHAR(50) NOT NULL, 
    [LastLogin] DATETIME NULL, 
    [PermissionGroup] INT NOT NULL
)
