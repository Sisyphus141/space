return {
    "neovim/nvim-lspconfig",
    event = { "BufReadPre", "BufNewFile" },
    dependencies = {
        "hrsh7th/cmp-nvim-lsp",
        { "antosha417/nvim-lsp-file-operations", config = true },
    },
    config = function()
        local lspconfig = require("lspconfig")
        local cmp_nvim_lsp = require("cmp_nvim_lsp")

        local opts = { noremap = true, silent = true }
        local keymap = vim.keymap.set

        local on_attach = function(client, bufnr)
            opts.buffer = bufnr

            keymap("n", "gR", "<cmd>Telescope lsp_references<CR>", opts)
            keymap("n", "gD", vim.lsp.buf.declaration, opts)
            keymap("n", "gd", "<cmd>Telescope lsp_definitions<CR>", opts)
            keymap("n", "gi", "<cmd>Telescope lsp_implementations<CR>", opts)
            keymap("n", "gt", "<cmd>Telescope lsp_type_definitions<CR>", opts)
            keymap({ "n", "v" }, "<leader>ca", vim.lsp.buf.code_action, opts)
            keymap("n", "<leader>rn", vim.lsp.buf.rename, opts)
            keymap("n", "<leader>D", "<cmd>Telescope diagnostics bufnr=0<CR>", opts)
            keymap("n", "<leader>d", vim.diagnostic.open_float, opts)
            keymap("n", "[d", vim.diagnostic.goto_prev, opts)
            keymap("n", "]d", vim.diagnostic.goto_next, opts)
            keymap("n", "K", vim.lsp.buf.hover, opts)
            keymap("n", "<leader>rs", ":LspRestart<CR>", opts)
        end

        local capabilities = cmp_nvim_lsp.default_capabilities()

        local signs = { Error = " ", Warn = " ", Hint = "󰠠 ", Info = " " }
        for type, icon in pairs(signs) do
            local hl = "DiagnosticSign" .. type
            vim.fn.sign_define(hl, { text = icon, texthl = hl, numhl = "" })
        end

        lspconfig.clangd.setup({
            capabilities = capabilities,
            on_attach = on_attach,
            filetypes = { "c", "cpp", "objc", "objcpp" },
            cmd = { "/usr/bin/clangd-14", "--background-index", "--suggest-missing-includes", "--clang-tidy" },
            settings = {
                clangd = {
                    fallbackFlags = {
                        "-std=c++17",
                        "-isystem/usr/include/c++/12",
                        "-isystem/usr/include/x86_64-linux-gnu/c++/12",
                        "-isystem/usr/include/c++/12/backward",
                        "-isystem/usr/lib/gcc/x86_64-linux-gnu/12/include",
                        "-isystem/usr/local/include",
                        "-isystem/usr/lib/gcc/x86_64-linux-gnu/12/include-fixed",
                        "-isystem/usr/include/x86_64-linux-gnu",
                        "-isystem/usr/include",
                    },
                },
            },
        })
    end,
}

